# Multiple-Choice-Exam-Generator

--- 

## Table of Contents
- [Overview](#overview)
- [Description](#description)
- [Languages tools and technologies](#languages-tools-and-technologies)
- [Project](#project)
- [Acknowledgement](#acknowledgement)
- [Author Info](#author-info)

---

## Overview
The multiple choice exam generator is a progrom developed using the C++ programming language to generates a multiple choice exam for students. The program allows the student to enter the amount of question he/she wishes to answer during the examination. The program then randomly display the user defined amount of questions to the student allowing him/her to take the exam. Each question is composed of four possible answers, one correct answer and three incorrect answers.  At the end of the exam a summary of the student performance in the exam is displayed.  

--- 

## Description
* The program read all the questions from the file, questions.txt, and store them in an array. This array is referred to as the Question Bank.
* The program then create an array of exam questions by randomly selecting the user defined number of questions from the Question Bank. The array of exam questions is referred to as the Exam. When a question is selected from the Question Bank, the four responses was shuffled, when necessary.
* The exam questions were then presented to the user, one by one. Three actions are possible when a question is displayed to the user:
  * The user answers the question correctly
  * The user answers the question incorrectly
  * The user skips the question
A record was kept of the user’s performance on each question to generate teh summary details.
* At the end of the examination, a summary of the user’s performance is given. The summary displays how many responses were correct or incorrect and how many questions were skipped. The total marks obtained by the user is also displayed.

---

## Languages tools and technologies
* C++
* Data structures

---

## Project
![Screenshot (630)](https://user-images.githubusercontent.com/77646306/124189408-a8f87b00-da8e-11eb-9988-d05eda37ff41.png)

---

## Acknowledgement
* COMP1602 - Assignment

---

## Author Info
* [Linkedin](https://www.linkedin.com/in/tamika-ramkissoon-1a2622214/)
