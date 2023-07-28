.macro SET reg,val
#if __NM4__== 0
	\reg = \val; 
#else
	sir = \val; 
	\reg = sir;   
#endif
.endm


.macro BRANCH 
#if __NM4__== 0
	.branch	
#endif
.endm

.macro WAIT 
#if __NM4__== 0
	.wait	
#endif
.endm
