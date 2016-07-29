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

			 
		  mov ebx, dim
			  shr ebx, 1

		rowForLoop:
			cmp edi, dim
			jae endRowLoop
			mov esi, 0

			colForLoop :
				cmp esi, ebx
				jae endColLoop
				mov a_p, 0
				mov edx, 0

				ap_mult :
					cmp edx, dim
					jae end_ap_mult
					add a_p, edi
					inc edx
					jmp ap_mult

				end_ap_mult :
				add a_p, esi
					 shl a_p, 2
			    add a_p, eax
			    mov edx, 0
			    mov a_p_m, 0


	  apm_mult :
		  cmp edx, dim

	      jae end_apm_mult
				  add a_p_m, edi
				  inc edx
		  jmp apm_mult

	  end_apm_mult :
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
		  jmp colForLoop

	  endColLoop :
		  inc edi
		  jmp rowForLoop

	  endRowLoop :
		  mov eax, image
			

	 
  }
}
