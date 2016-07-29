//
//	ICS 51, Lab #2
//
//	-----------------------------------------------------------------
// 
//	IMPORTATNT NOTES:
//	
//	- To test your code use the tests in lab2-testing.cpp
//	
//	- Write your assembly code only in the marked blocks.
//	
//	- Do NOT change anything outside the marked blocks.
//
//	- Remember to fill in your name, student ID below.
// 
//	- This lab has to be done individually.
//
//  - Use lodepng.h and lodepng.cpp to read/write png files.
//
//  - Two test images are provided to you.
//	
//	- Submit ONLY lab2.cpp file for grading.
// 


char *yourName = "Solomon Chan";
char *yourStudentID = "40786337";


//
// This function should takes in a square sized grayscale image and applies thresholding on each pixel.
// Width and height of the image are equal to dim.
// NOTE: you can't define additional variables.
//
void imageThresholding(unsigned char* image, int dim) {
	
	__asm {
    
// YOUR CODE STARTS HERE
		mov eax, image
		mov edi, 0

		ForRowLoop:
			cmp dim, edi
			jle finish
			mov esi, 0

		ForColLoop:
			mov ebx, 0 
			mov edx, 0 
			cmp dim, esi
			jle exitColLoop
			
		mulForLoop:
			cmp dim, edx
			jle exitMulLoop
			add ebx, edi
			add edx, 1
			jmp mulForLoop

		exitMulLoop:
			
				xor edx, edx
				add ebx, esi

				mov dl, [eax + ebx] 
				mov cl, 0x80
				
				and cl, dl
				cmp cl, 0x00
				jne greaterThan

				xor edx, edx 
				jmp run

				greaterThan:
					or edx, 0xFFFFFFFF

				run:
					mov [eax + ebx], dl
					add esi, 1
					jmp forColLoop

		exitColLoop:
			add edi, 1
			jmp ForRowLoop

		finish: 
			mov image, eax

// YOUR CODE ENDS HERE
  }
}

// This function flips an square iamge of given dimension horizontally/vertically.
// Width and height of the image are equal to dim.
// if direction is 0, image should be flipped horizontally
// otherwise image should be flipped vertically.
//
//
// Two variables are definde to help you with implemetanion.
// NOTE: you can't define additional variables.
//
void imageFlip(unsigned int* image, int dim, int direction) {
  
  unsigned int a_p, a_p_m;
  
  __asm {
    
// YOUR CODE STARTS HERE
	  //Load Variables
mov eax, image
mov edi, 0
mov edx, direction
cmp edx, 1
jae VERTICAL
mov ebx, dim
shr ebx, 1
I_LOOP:
cmp edi, dim
jae END_I_LOOP
mov esi, 0
J_LOOP :
cmp esi, ebx
jae END_J_LOOP
mov a_p, 0
mov edx, 0
AP_LOOP :
cmp edx, dim
jae END_AP_LOOP
add a_p, edi
inc edx
jmp AP_LOOP
END_AP_LOOP :
add a_p, esi
shl a_p, 2
add a_p, eax
mov edx, 0
mov a_p_m, 0
APM_LOOP :
cmp edx, dim
jae END_APM_LOOP
add a_p_m, edi
inc edx
jmp APM_LOOP
END_APM_LOOP :
mov edx, dim
sub edx, esi
dec edx
add a_p_m, edx
shl a_p_m, 2
add a_p_m, eax
mov ecx, a_p
mov ecx, [ecx]
mov edx, a_p_m
mov edx, [edx]
mov eax, a_p_m
mov [eax], ecx
mov eax, a_p
mov [eax], edx
mov eax, image
inc esi
jmp J_LOOP
END_J_LOOP :
inc edi
jmp I_LOOP
END_I_LOOP :
mov eax, image
jmp END_OF_CODE
//Verticzl
VERTICAL:
mov ebx, dim
shr ebx, 1
V_I_LOOP :
cmp edi, ebx
jae V_END_I_LOOP
mov esi, 0
V_J_LOOP :
cmp esi, dim
jae V_END_J_LOOP
mov a_p, 0
mov edx, 0
V_AP_LOOP :
cmp edx, dim
jae V_END_AP_LOOP
add a_p, edi
inc edx
jmp V_AP_LOOP
V_END_AP_LOOP :
add a_p, esi
shl a_p, 2
add a_p, eax
mov edx, 0
mov a_p_m, 0
mov ecx, dim
sub ecx, edi
dec ecx
V_APM_LOOP :
cmp edx, dim
jae V_END_APM_LOOP
add a_p_m, ecx
inc edx
jmp V_APM_LOOP
V_END_APM_LOOP :
add a_p_m, esi
shl a_p_m, 2
add a_p_m, eax
mov ecx, a_p
mov ecx, [ecx]
mov edx, a_p_m
mov edx, [edx]
mov eax, a_p_m
mov[eax], ecx
mov eax, a_p
mov[eax], edx
mov eax, image
inc esi
jmp V_J_LOOP
V_END_J_LOOP :
inc edi
jmp V_I_LOOP
V_END_I_LOOP :
mov eax, image
END_OF_CODE:
// YOUR CODE ENDS HERE
  }
}
