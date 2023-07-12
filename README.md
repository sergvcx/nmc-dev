/include    заголовочные файлы: *.h  
/nm         исходники для NMC:  *.S *.cpp  
/pc         исходники для x86:  *.cpp        
/common     общие исходники NMC+x86: *.cpp (обычно функции инициализации)   
/test       папка с тестами соcтоит из полноценных проектов с запуском на x86/nmc/qemu). Одна функция - один тест (main.cpp)  
/dev-xxx    личная песочница    
   
# nmc



# Замечания по оформлению
void nmppsHadamardInitSort(nm2s* Hsrc, nm2s* Hdst, int size);

Пока используем camelCase стиль . Cоответсвенно переменные/аргументы  надо так:
void nmppsHadamardInitSort(nm2s* hSrc, nm2s* hDst, int size);

однако h полезной информации не несет . Желательно  полностью расшифровать до: srcNaturalOrderdMtr , dstSequencyOrderedMtr, либо вообще опустить до src,dst .
Идеальное именование - когда переменные описывают сами себя и документация в идеале не требуется. Поэтому лучше первое. 

Если выход нельзя писать на выход (так называемый inplace невозможен), как в данной фунции , то указатель на неизменяемый массив обьявлем как const*

size - путает что есть рамер , то ли общий размер, то ли размерность (ширина ,высота) , соотно лучше имя dim 

В итоге:
void nmppsHadamardInitSort(const nm2s* srcNaturalOrderdMtr, nm2s* dstSequencyOrderedMtr, int dim);


#Тесты 
test_hadamard 
тесты и так лежат в папке test. Префикс test_  не требуется

для сборки тестов не хватает .ld файлов. Положить рядом с Makefile 


