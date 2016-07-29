/*
	ICS 51. Lab #3

	IMPORTATNT NOTES:

	- Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the
	__declspec(naked) attribute is used, it is the programmer's responsibility to write the
	prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only
	for the functions that have been declared with the naked attribute, namely:

	   + findMinIndex
	   + recFactorial
	   + performOperation
	   + fibonacci

	- You cannot define any local variable in the C code. If you need additional variables in your
	assembly code, you have to allocate space for them in the prologue of the function.

	- You are not allowed to change anything in this file except for adding your assembly code
    between the lines marked "BEGIN YOUR CODE HERE" and "END YOUR CODE HERE".

	- Remember to fill in your name, student ID below.

	- ONLY submit the lab3.c file for grading.

*/

char *yourName = "Solomon Chan";
char *yourStudentID = "40786337";

/***********************************************************************************************

	PART 1: Selection Sort

	Selection sort is an in-place comparison sort algorithm that works by dividing the input list
	into two parts: the sublist of items already sorted, which is built up from left to right of
	the list, and the sublist of items remaining to be sorted that occupy the rest of the list.
	Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
	The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it
	with the leftmost unsorted element (putting it in sorted order), and moving the sublist
	boundaries one element to the right. To learn more, read:
	https://en.wikipedia.org/wiki/Selection_sort#Example

	Our implementation here uses a function called "findMinIndex" to find the index of smallest
	element between ith index and jth index of the array. The function "selectionSort" uses
	this function to find the smallest number and exchanges it with the leftmost unsorted element
	in each iteration. You need to implement the behavior of both functions in x86 assembly.

************************************************************************************************/

__declspec(naked)
int findMinIndex (int integer_array[], int i, int j)
{

// C code to be converted to x86 assembly
/*
    int iMin = i;
    // test against elements after i and before j to find the smallest
    for ( i ; i < j; i++) {
        // if this element is less, then it is the new minimum
        if (integer_array[i] < integer_array[iMin]) {
            // found new minimum; remember its index
            iMin = i;
        }
    }

    return iMin;
*/

	__asm{
			// BEGIN YOUR CODE HERE
		push ebp
		mov ebp, esp
		push edi
		push esi
		push ebx
		mov eax, [ebp + 8]
		mov edx, [ebp + 12]
		mov ecx, [ebp + 16]
		mov ebx, edx
	forLoop:
		cmp edx, ecx
		jge exitLoop
		mov esi, [eax + 4 * edx]
		mov edi, [eax + 4 * ebx]
		cmp esi, edi
		jge ifLoop
		mov ebx, edx
	ifLoop:
		inc edx
		jmp forLoop
	exitLoop:
		mov eax, ebx
		pop ebx;
		pop esi
		pop edi
		mov esp, ebp
		pop ebp
			// END YOUR CODE HERE
			ret
	}
}

void selectionSort (int integer_array[], int array_size)
{

// C code to be converted to x86 assembly
/*
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
 		iMin = findMinIndex (integer_array, j, array_size);

		if(iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array [j];
			integer_array[j] = temp;
		}
	}
*/

	__asm{
			// BEGIN YOUR CODE HERE
		mov esi, integer_array
		mov edx, array_size
		sub edx, 1
		xor edi, edi
		forLoop:
		cmp edi, edx
		jge exitLoop
		push eax
		push ecx
		push edx
		mov ebx, array_size
		push ebx
		push edi
		push esi
		call findMinIndex
		add esp, 12
		mov ebx, eax
		pop edx
		pop ecx
		pop eax
		cmp ebx, edi
		je ifLoop
		mov eax, [esi + 4 * ebx]
		mov ecx, [esi + 4 * edi]
		xor eax, ecx
		xor ecx, eax
		xor eax, ecx
		mov[esi + 4 * ebx], eax
		mov[esi + 4 * edi], ecx
	ifLoop:
		inc edi
		jmp forLoop
	exitLoop:
		mov integer_array, esi
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 2: Recursive Factorial

	Implement two functions that calculates the factorial of an integer not greater than 12.

	The 1st function, factorial (unsigned int input, unsigned int *output), is the non
	recursive wrapper function which takes the input, sets up the stack, calls the recursive
	function and finally puts the result in the location pointed to by the pointer argument called
    output.

	The 2nd function, recFactorial(unsigned int n), is the recursive function that actually
	calculates the factorial.

	Given an unsigned integer number n,we define FACTORIAL(n) as:

        FACTORIAL(n) =  1                   ,    if n = 0 or n = 1
                        n * FACTORIAL(n-1)  ,    if n > 1

	Tip:

	- You need to use IMUL instruction to multiply unsigned integers. Learn how to use it:
	http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#instructions

************************************************************************************************/

__declspec(naked)
unsigned int recFactorial (unsigned int n)
{

// C code to be converted to x86 assembly
/*
	if (n<=1)
		return 1;
	else
		return n * recFactorial(n-1);
*/

	__asm{
			// BEGIN YOUR CODE HERE
		push ebp
		mov ebp, esp
		push edi
		push esi
		push ebx
		mov ebx, [ebp + 8]
		cmp ebx, 1
		ja infLoop
		mov eax, 1
		jmp exitLoop
	infLoop:
		push eax
		push ecx
		push edx
		dec ebx
		push ebx
		call recFactorial
		add esp, 4
		mov ebx, eax
		pop edx
		pop ecx
		pop eax
		imul ebx, [ebp + 8]
		mov eax, ebx
	exitLoop:
		pop ebx
		pop esi
		pop edi
		mov esp, ebp
		pop ebp

			// END YOUR CODE HERE
			ret
	}
}

void factorial (unsigned int input, unsigned int *output)
{

// C code to be converted to x86 assembly
/*
	*output = recFactorial (input);
*/

	__asm{
			// BEGIN YOUR CODE HERE
		push eax
		push ecx
		push edx
		mov eax, input
		push eax
		call recFactorial
		add esp, 4
		mov ebx, output
		mov[ebx], eax
		pop edx
		pop ecx
		pop eax
			// END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 3: Vector Operation

	The vectorOperations function gets as parameters 4 arrays of the same length and
	the number of elements in those arrays.

	For each pair of elements in first_array and second_array, it calls performOperation
	and stores the returned result in the same index of output_array.

	output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

	You also need to implement the body of performOperation function according to the provided
	C code.

************************************************************************************************/

__declspec(naked)
int performOperation (int operation, int first, int second)
{

// C code to be converted to x86 assembly
/*
	if (operation==0)
		return first + second;
	else if (operation==1)
		return first - second;
	else if (operation==2)
		return (first > second)? first : second;
	else if (operation==3)
		return (first < second)? first : second;
	else
		return first;
*/

	__asm {
			// BEGIN YOUR CODE HERE

		push ebp
		mov ebp, esp
		sub esp, 4
		push edi
		push esi
		push ebx
		mov ebx, [ebp + 8]
		mov ecx, [ebp + 12]
		mov edx, [ebp + 16]
		cmp ebx, 0
		jne secondIf
		mov[ebp - 4], ecx
		add [ebp - 4], edx
		mov eax, [ebp - 4]
		jmp proceed
	secondIf:
		cmp ebx, 1
		jne thirdIf
		mov[ebp - 4], ecx
		sub[ebp - 4], edx
		mov eax, [ebp - 4]
		jmp proceed
	thirdIf:
		cmp ebx, 2
		jne fourthIf
		cmp ecx, edx
		jle thirdAlternative
		mov eax, ecx
		jmp proceed
	thirdAlternative:
		mov eax, edx
		jmp proceed
	fourthIf:
		cmp ebx, 3
		jne otherWise
		cmp ecx, edx
		jge fourthVariant
		mov eax, ecx
		jmp proceed
	fourthVariant:
		mov eax, edx
		jmp proceed
	otherWise:
		mov eax, ecx
	proceed:
		pop ebx
		pop esi
		pop edi
		mov esp, ebp
		pop ebp
			// END YOUR CODE HERE
			ret
	}
}

void vectorOperations (int number_of_elements, int *first_array, int *second_array,
					   int *operation_array, int *output_array)
{
// C code to be converted to x86 assembly
/*
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
	}
*/
	__asm {
			// BEGIN YOUR CODE HERE
		mov edi, output_array
		xor esi, esi
	forLoop:
		cmp esi, number_of_elements
		jge exitLoop
		push eax
		push ecx
		push edx
		mov eax, second_array
		mov eax, [eax + 4*esi]
		mov ebx, first_array
		mov ebx, [ebx + 4*esi]
		mov ecx, operation_array
		mov ecx, [ecx + 4*esi]
		push eax
		push ebx
		push ecx
		call performOperation
		add esp, 12
		mov[edi + 4*esi], eax
		pop edx
		pop ecx
		pop eax
		inc esi
		jmp forLoop
	exitLoop:
		mov output_array, edi
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 4: Change Letter Case

	You are given an array of characters (a string) that may contain numbers, upper and	lower case
    letters, punctuations symbols, etc. Implement a function to convert all uppercase letters to
    lowercase and vice versa.
    For example "ThisIsTheFinalLabOf51" should be converted to "tHISiStHEfINALlABoF51".
	The function has the following argument: An array of charaters and the size of the array. The
	array should be changed in place. There is no explicit output for this function.

	Tips:

	- Note that each element of the arrays is a char (1 byte). You can NOT use a 32-bit register
	to read/write from/to a memory location. Instead you should use the 8-bit version of the x86
	general-purpose registers.
	More info: http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#registers

	- The link to the ascii codes is here: http://www.asciitable.com/

************************************************************************************************/

void changeCase (char char_array[], int array_size ) {
	__asm{
			// BEGIN YOUR CODE HERE
		mov edx, char_array
		xor esi, esi
	forLoop:
		cmp esi, array_size
		jge exitLoop
		mov al, byte ptr[edx + esi]
		cmp al, 65
		jl next
		cmp al, 90
		jg next
		add al, 32
		mov byte ptr[edx + esi], al
		jmp proceed
	next:
		cmp al, 97
		jl proceed
		cmp al, 122
		jg proceed
		and al, 95
		mov byte ptr[edx + esi], al
	proceed:
		inc esi
		jmp forLoop
	exitLoop:
		mov char_array, edx
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 5: Fibonacci

	Implement a recursive function in assembly which returns the Nth number in the fibbonaci
	series (1, 1, 2, 3, 5, 8, ...).

************************************************************************************************/

__declspec(naked)
unsigned int fibonacci (unsigned int n) {

// C code to be converted to x86 assembly
/*
	if (n < 2)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
*/

	__asm{
			// BEGIN YOUR CODE HERE
		push ebp
		mov ebp, esp
		push edi
		push esi
		push ebx
		mov ebx, [ebp + 8]
		cmp ebx, 2
		jae infLoop
		mov eax, 1
		jmp exit
	infLoop:
		push eax
		push ecx
		push edx
		mov ecx, ebx
		dec ecx
		push ecx
		call fibonacci
		add esp, 4
		mov esi, eax
		mov ecx, ebx
		sub ecx, 2
		push ecx
		call fibonacci
		add esp, 4
		mov edi, eax
		pop edx
		pop ecx
		pop eax
		mov eax, esi
		add eax, edi
	exit:
		pop ebx
		pop esi
		pop edi
		mov esp, ebp
		pop ebp

			// END YOUR CODE HERE
			ret
	}
}