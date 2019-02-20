#include <wiringPi.h>
#include <iostream>

void flashSequence(char* sequence);
void flashDotOrDash(char dotOrDash);
void flashSequence(char* sequence);
void flashMessage(char* message);

char* letters[] = {
".-", 	// A
"-...",	// B
"-.-.", // C
"-..", 	// D
".", 	// E
"..-.",	// F 
"--.", 	// G
"....", // H
"..", 	// I
".---", // J
"-.-", 	// K
".-..", // L
"--", 	// M
"-.", 	// N
"---", 	// O
".--.", // P
"--.-", // Q
".-.", 	// R 
"...", 	// S
"-", 	// T
"..-", 	// U
"...-", // V 
".--", 	// W
"-..-", // X
"-.--", // Y
"--.." 	// Z
};
char* numbers[] = {
	"-----", // 0
	".----", // 1
	"..---", // 2
	"...--", // 3
	"....-", // 4
	".....", // 5
	"-....", // 6
	"--...", // 7
	"---..", // 8
	"----."};// 9

int dotDelay = 100;
int ledPin = 0;
#define BUFFER_SIZE 20
char message[BUFFER_SIZE] = "SOS";
char buffer[BUFFER_SIZE]; 

int main (void)
{
	wiringPiSetup();
	pinMode(ledPin,OUTPUT);
	
	while(1)
	{
		std::cin.get(buffer, BUFFER_SIZE-1, '\n');
		std::cin.clear();
		std::cin.ignore(10000,'\n');		
		flashMessage(buffer);				
	}
	return 0;
}

void flashMessage(char* message)
{
	
	int i = 0;
	while (message[i] != '\0')
	{
		char ch = message[i++];		
		if (ch >= 'a' && ch <= 'z')
		{
			flashSequence(letters[ch - 'a']);
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			flashSequence(letters[ch - 'A']);
		}
		else if (ch >= '0' && ch <= '9')
		{
			flashSequence(numbers[ch - '0']);
		}
		else if (ch == ' ')
		{
			delay(dotDelay * 16); // gap between words
		}
	}
}

void flashSequence(char* sequence)
{
	int i = 0;
	while (sequence[i] != '\0')
	{
		flashDotOrDash(sequence[i]);
		i++;
	}
	delay(dotDelay * 6); // gap between letters
}
void flashDotOrDash(char dotOrDash)
{
	digitalWrite(ledPin, HIGH);
	if (dotOrDash == '.')
	{
		delay(dotDelay);
	}
	else // must be a -
	{
		delay(dotDelay * 8);
	}
	digitalWrite(ledPin, LOW);
	delay(dotDelay*3); // gap between flashes
}
	
