#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <conio.h>

using namespace std;

#define NUM_CHOICES 4

//declaration of structs used within the program.
struct Responses {
	string text[4];
	string answer;
	bool shuffle;
};

struct Question {
	string ID;
	string text;
	Responses responses;
	int points;
};

struct Summary {
	string questionID;
	bool correct;
	bool skipped;
	string answer;
	string givenAnswer;
	int points;
};

// This function reads all the questions from questions.txt into 
// the Question Bank. It returns the amount of questions in the 
// Question Bank.

int readQuestions (Question questionBank[]) { 
	
	int numQuestions = 0, i =0;
	string ID, question, text, blank, answer;
	bool shuffle;
	int points;
	
	Question questionDetails;
	
	ifstream in;
	in.open("Questions.txt");
	
	// if statement to check whether the input file was successfully opened.
	if (!in.is_open())
	{
		cout << "There was an error opening the data file!  Operation aborting!!..." << endl;
		exit(1);
	}
	else 
		cout << "Input file sucessfully opened..." << endl;
		
	cout << "Reading Question from file!..." << endl;
	
	getline(in, ID);
		
	while ((ID != "END") && (numQuestions <= 100)){
		questionDetails.ID = ID;
		
		getline(in, text);	
		questionDetails.text = text;
		
		for(i = 0; i < NUM_CHOICES; i = i + 1){
			getline(in, question);
			questionDetails.responses.text[i] = question;
		}
	
		getline(in, answer);
		questionDetails.responses.answer = answer;
	
		in >> shuffle;
		questionDetails.responses.shuffle = shuffle;
		
		in >> points;
		questionDetails.points = points;		
				
		getline(in, blank); // reads the bool data for shuffle
		getline(in, blank);// reads the int data for # of points
		
		questionBank[numQuestions] = questionDetails;
		numQuestions = numQuestions + 1;
		getline(in, ID);
	}	
	
	in.close();

	return numQuestions;
}

// This function returns true if the exam already contains
// the question with the given questionID and false, otherwise.

bool containsQuestion (Question exam[], int numExamQuestions, string questionID) { 
	
	int i;
	for (i =0; i <= numExamQuestions; i = i + 1){
		if(exam[i].ID == questionID){
			return true;
		}
	}
	
	return false;
}

// This function accepts the question passed as a parameter, 
// shuffles the responses if the responses should be shuffled, 
// and returns the modified question.

Question shuffleResponses (Question question) { // this is the function 
	
	string temp;								
	int i;			
	int randomIndex;
	int Loc;
								
	srand(time(NULL));
	
	for (i = 0; i < NUM_CHOICES; i = i + 1){
		randomIndex = rand() % NUM_CHOICES;
		temp = question.responses.text[i];
		question.responses.text[i]= question.responses.text[randomIndex];
		question.responses.text[randomIndex]= temp;
		
	}
		
	return question; 
}

// This function creates the exam containing numExamQuestions, 
// where the questions are taken randomly from the Question Bank, 

void prepareExam (Question questionBank[], int numQuestions, Question exam[], int numExamQuestions) { 

	int i =0, j, randomIndex;
	bool newQuestion;
	 
	srand(time(NULL));

	while(i < numExamQuestions){
		randomIndex = rand() % numQuestions;
		newQuestion	= containsQuestion(exam, numExamQuestions, questionBank[randomIndex].ID);
		if(newQuestion == false){
		exam[i].ID = questionBank[randomIndex].ID;  
		exam[i].text = questionBank[randomIndex].text;
			for (j = 0; j < NUM_CHOICES; j = j + 1){
			exam[i].responses.text[j] = questionBank[randomIndex].responses.text[j];
			}
		exam[i].points = questionBank[randomIndex].points;
		exam[i].responses.answer = questionBank[randomIndex].responses.answer;
		exam[i].responses.shuffle = questionBank[randomIndex].responses.shuffle;
		i = i + 1;
		}
	}
}

// After the exam is prepared, this function presents the 
// questions on the exam to the user, one by one. It also
// records how the user responded to each question, for 
// the summary at the end.

void generateExam (Question exam[], int numExamQuestions, Summary summary[]) { 

	int i, j, givenAnswer, skip = 5;
	Question shuffled;
	int option, loc;

	cout << "Exam prepared and about to begin\n" << endl;
	cout <<  "GOOD LUCK!\n" << endl;
	
	system("pause");
	system("cls");
	
	
	for (i = 0; i < numExamQuestions; i = i + 1){
		cout << "\n\nQuestion ID: " << exam[i].ID << endl;
		cout << "\n" << exam[i].text <<endl;
		if (exam[i].responses.shuffle == 1){
			shuffled = shuffleResponses(exam[i]);
			
			for ( j = 0; j < NUM_CHOICES; j = j + 1)
			{
				cout << j + 1 << ". " << shuffled.responses.text[j] << endl;
			}
	
		cout << "\nEnter you response here [ 1, 2, 3, 4, OR 5 to skip] ";
		
		
		cin >> option;
		loc = option - 1;
		}
			
		else if (exam[i].responses.shuffle == 0){
		
			shuffled = exam[i];
			
			for ( j = 0; j < NUM_CHOICES; j = j + 1)
			{
				cout << j + 1 << ". " << shuffled.responses.text[j] << endl;
			}
		
			cout << "\nEnter you response here [ 1, 2, 3, 4, OR 5 to skip] ";
			cin >> option;
			loc = option - 1;
		}
		if	(option == skip){
			cout << "Skipped";
			summary[i].givenAnswer = "5";
			summary[i].questionID = exam[i].ID;
			summary[i].skipped = true;
			summary[i].points = 0; 
			summary[i].answer = exam[i].responses.answer;
		}
			
		else if (exam[i].responses.answer == shuffled.responses.text[loc]){
			cout << "Correct";
			summary[i].givenAnswer = shuffled.responses.text[loc];
			summary[i].questionID = exam[i].ID;
			summary[i].correct = true;
			summary[i].points = exam[i].points;
			summary[i].answer = exam[i].responses.answer;
		}
					
		else if(exam[i].responses.answer != shuffled.responses.text[loc]){
			cout << "Incorrect";
			summary[i].givenAnswer = shuffled.responses.text[loc];
			summary[i].questionID = exam[i].ID;
			summary[i].correct = false;
			summary[i].points = 0;
			summary[i].answer = exam[i].responses.answer;
		}
		
		cout << endl;
		system ("pause");
		system("cls");
	}
	
}


// This function displays a summary of the user's performance on 
// each question of the exam, after the exam is completed.

void displaySummary (Summary summary[], int numExamQuestions) {
	int i;
	int correct =0, incorrect =0, skipped=0 ;
	int correctPoints = 0;
	
	cout << "\n\nExam Summary " << endl;
	for(i = 0; i < numExamQuestions; i = i + 1){
		cout << "\nQuestion:      " << i + 1 <<endl;
		cout << "Question ID:   " << summary[i].questionID << endl;
		cout << "Correct:       ";
		if (summary[i].correct == true){
			cout << "Yes" <<endl;
			cout << "Marks:         " << summary[i].points << endl;
			correct = correct + 1;
			correctPoints = correctPoints + summary[i].points;
		}
		if ((summary[i].correct == false) && (summary[i].skipped == false)){
			cout << "No" << endl;
			cout << "Marks:         0"  << endl;
			incorrect = incorrect + 1;
		}
		if (summary[i].skipped == true){
			cout << "Skipped" << endl;
			cout << "Marks:         0"  << endl;
			skipped = skipped + 1;
		}
		cout << "Correct Answer:" << summary[i].answer <<endl;
		cout << "Answer Given:  " << summary[i].givenAnswer <<endl;
		cout << endl;
	}
	cout << "\n\nSummary: " << endl;
	cout << "======== " << endl;
	cout << "Correct Answers:   " << correct << endl;
	cout << "Incorrect Answers: " << incorrect << endl;
	cout << "Skipped Answers:   " << skipped << endl;
	cout << "Total Marks:       " << correctPoints << endl;
}


// The main function calls readQuestions, prepareExam, 
// generateExam, and displaySummary to achieve the functionality
// of Assignment 1.

int main () {

	// Declarations for questionBank, exam, and summary
	
	Question questionBank[100];
	int numQuestions, i;
	

	Question exam [50];
	int numExamQuestions;
	
	Summary summary [50];
	

	numQuestions = readQuestions(questionBank);
	cout << numQuestions << " question read from file and stored in questionBank!..." <<endl;
	
	cout << "\nPlease enter the amount of questions in the exam! (must be less than or equal to " << numQuestions << ") " ;
	cin >> numExamQuestions;
	
	if (numExamQuestions > numQuestions){
		cout << "Invalid Number, Please enter a number less than or equal to " << numQuestions << " !! " << endl;
		cin >> numExamQuestions;
	}
	system("pause");
	system("cls");
	cout << "		Multiple Choice Exam Generator" << endl;
	cout << "		==============================" << endl;
	prepareExam (questionBank, numQuestions, exam, numExamQuestions); 
	generateExam (exam, numExamQuestions, summary); 
	displaySummary (summary, numExamQuestions);
	
    return 0;
}

