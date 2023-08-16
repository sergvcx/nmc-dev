#include "c:/Module/nmc-dev/nmc-dev/include/hadamard.h"
#include "c:/module/nmpp-nm6407-2.1.6-win64/include/nmpp.h"

void getHadamardProduct_32s(nm32s* srcA, nm32s* srcB, nm32s* dst, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst[i * width + j] = srcA[i * width + j] * srcB[i * width + j];
		}
	}
};

#include <windows.h>
#include <vector>
#include "VShell.h"

namespace {
	void SmoothFilter(const std::vector<BYTE>& vecSrc, std::vector<BYTE>& vecDst, int nWidth, int nHeight, int nFilterSize) {
		int i, j, k, m, nInd, nTmp;

		for (i = 0; i < (nHeight - nFilterSize); i++)
			for (j = 0; j < (nWidth - nFilterSize); j++) {
				nInd = i * nWidth + j;
				nTmp = 0;
				for (k = 0; k < nFilterSize; k++)
					for (m = 0; m < nFilterSize; m++)
						nTmp += vecSrc[nInd + k * nWidth + m];
				vecDst[nInd + (nFilterSize / 2) * (nWidth + 1)] = (BYTE)(nTmp / (nFilterSize * nFilterSize));
			}
	}
}

int main()
{
	if (!VS_Init())
		return 0;
	if (!VS_Bind("../examples/lena.bmp"))
		return 0;

	int W = VS_GetWidth(VS_SOURCE);
	int H = VS_GetHeight(VS_SOURCE);

	VS_STOP_COLOR pStopColor[3] = {
	VS_MAKE_STOP_COLOR(0,VS_LIME),
	VS_MAKE_STOP_COLOR(1,VS_RED),
	VS_MAKE_STOP_COLOR(2,VS_YELLOW)
	};
	S_VS_Pal FilterPalette[256];
	VS_CreateCustomPalette(FilterPalette, pStopColor, sizeof(pStopColor)/4);

	std::vector<BYTE> vecOriginal;
	std::vector<int> src32, srcChess32, dst32, spectrum32, temp32, Y32, filter;
	std::vector<short> src16, srcChess16, dst16, spectrum16, temp16, Y16;
	std::vector<long long> Had, Had_seq;

	vecOriginal.resize(W * H);

	src32.resize(W * H);
	srcChess32.resize(W * H * 4);
	dst32.resize(W * H * 4);
	spectrum32.resize(W * H * 4);
	temp32.resize(W * H * 4);
	Y32.resize(W * H * 4);
	filter.resize(W * H * 4);

	src16.resize(W * H);
	srcChess16.resize(W * H * 4);
	dst16.resize(W * H * 4);
	spectrum16.resize(W * H * 4);
	temp16.resize(W * H * 4);
	Y16.resize(W * H * 4);

	Had.resize(W * (H / 8));
	Had_seq.resize(W * (H / 8));

	VS_CreateImage("Original", 0, W, H, VS_GetType(VS_SOURCE), NULL);
	VS_CreateImage("Chess 32", 1, W * 2, H * 2, VS_RGB8_32, NULL);
	VS_CreateImage("Chess 16", 2, W * 2, H * 2, VS_RGB8_16, NULL);
	VS_CreateImage("Interp 32", 3, W * 2, H * 2, VS_RGB8_32, NULL);
	VS_CreateImage("Interp 16", 4, W * 2, H * 2, VS_RGB8_16, NULL);
	VS_CreateImage("Filter", 5, W * 2, H * 2, VS_RGB8_32, FilterPalette);
	VS_CreateImage("Spectrum 32", 6, W * 2, H * 2, VS_RGB32, NULL);
	VS_CreateImage("Spectrum 16", 7, W * 2, H * 2, VS_RGB16, NULL);

	VS_CreateEdit("Filter size", 0);
	VS_CreateSlider("Had", 0, 0, W * 4, 1, W*2);

	VS_CreateEdit("Filter size", 0);
	VS_SetEditInt(0, 3);

	// Hadamard transform
	nmppsHadamardInit((nm2s*)&Had[0], H * 2);
	nmppsHadamardInitSort((nm2s*)&Had[0], (nm2s*)&Had_seq[0], H * 2);

	while (VS_Run()) {
		VS_GetGrayData(VS_SOURCE, &vecOriginal[0]);
		VS_SetData(0, &vecOriginal[0]);

		for (int i = 0; i < W * H; i++) {
			src32[i] = vecOriginal[i];
			src16[i] = vecOriginal[i];
		}

		// generating checkerboard pattern
		memset(&srcChess32[0], 0, H * W * sizeof(int));
		memset(&srcChess16[0], 0, H * W * sizeof(short));
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				srcChess32[i * W * 4 + j * 2] = src32[i * W + j];
				srcChess32[i * W * 4 + j * 2 + W * 2 + 1] = src32[i * W + j];

				srcChess16[i * W * 4 + j * 2] = src16[i * W + j];
				srcChess16[i * W * 4 + j * 2 + W * 2 + 1] = src16[i * W + j];
			}
		}
		VS_SetData(1, &srcChess32[0]);
		VS_SetData(2, &srcChess16[0]);

		// generating filter of type 4
		int slider_num = VS_GetSlider(0);
		memset(&filter[0], 0, H * W * 4 * sizeof(int));
		for (int i = 0; i < H * 2; i++) {
			for (int j = 0; j < W * 2; j++) {
				if ((i + j < slider_num))
					filter[i * H * 2 + j] = 2;
				if ((i + j == slider_num))
					filter[i * H * 2 + j] = 1;
			}
		}
		VS_SetData(5, &filter[0]);

		// applying transform to get spectrum
		nmppsHadamard(&srcChess32[0], &spectrum32[0], (nm2s*)&Had_seq[0], &temp32[0], H * 2);
		nmppsHadamard_16s(&srcChess16[0], &spectrum16[0], (nm2s*)&Had_seq[0], &temp16[0], H * 2);
		VS_SetData(6, &spectrum32[0]);
		VS_SetData(7, &spectrum16[0]);

		// applying filter
		for (int i = 0; i < H * 2; i++) {
			for (int j = 0; j < W * 2; j++) {
				switch (filter[i * H * 2 + j]) {
				case 0:
					Y32[i * H * 2 + j] = 0;
					Y16[i * H * 2 + j] = 0;
					break;
				case 1:
					Y32[i * H * 2 + j] = spectrum32[i * H * 2 + j] >> 1;
					Y16[i * H * 2 + j] = spectrum16[i * H * 2 + j] >> 1;
					break;
				case 2:
					Y32[i * H * 2 + j] = spectrum32[i * H * 2 + j];
					Y16[i * H * 2 + j] = spectrum16[i * H * 2 + j];
					break;
				default:
					break;
				}
			}
		}

		// inverse Hadamard transform
		nmppsHadamardInverse(&Y32[0], &dst32[0], (nm2s*)&Had_seq[0], &temp32[0], H * 2);
		nmppsHadamardInverse_16s(&Y16[0], &dst16[0], (nm2s*)&Had_seq[0], &temp16[0], H * 2);

		// fixing colors
		for (int i = 0; i < H * 2; i++) {
			for (int j = 0; j < W * 2; j++) {
				dst32[i * H * 2 + j] <<= 1;
				dst16[i * H * 2 + j] <<= 1;
			}
		}

		VS_SetData(3, &dst32[0]);
		VS_SetData(4, &dst16[0]);

		VS_Draw(VS_DRAW_ALL);
	}

	return 0;
}

