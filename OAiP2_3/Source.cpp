#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

struct Queue
{
	int number;
	Queue* prev, * next;
};

void pushQueue(Queue*& begin, Queue*& end, int number, bool is_start);
Queue* viewQueue(Queue* begin, Queue* end, bool is_from_end);
Queue* individualTask1(Queue*& begin, Queue*& end, Queue*& max);
Queue* individualTask2(Queue*& begin, Queue*& end, int& max_number);
void createQueue(Queue*& begin, Queue*& end, int number);
void deleteQueue(Queue*& begin);
void fillQueue(Queue*& begin, Queue*& end, bool is_new = false);
bool isCorrectTask(Queue*& begin, Queue*& max, int& max_number);
int popQueue(Queue*& begin, Queue*& end);
int correctInputInt();

int main()
{
	Queue* begin = NULL, * end = NULL, * max = NULL, * new_Queue = NULL, * new_Queue_end = NULL;
	int max_number;
	char symbol;
	bool is_from_end = true;
	cout << "Do you want to see queue from the start?(Y/N)" << endl;
	symbol = _getch();
	if (symbol == 'Y' || symbol == 'y')
	{
		is_from_end = false;
	}
	while (true)
	{
		int code = 0, variable = 0;
		do
		{
			cout << "\n Create - 1\n Add - 2\n Individual task_variant1 - 3\n Individual task_variant2 - 4\n View Queue - 5\n Delete Queue - 6\n EXIT - 0\n";
			code = correctInputInt();
		} while (code < 0 || code > 6);
		switch (code)
		{
		case 1:
		case 2:
			if (code == 1 && begin != NULL)
			{
				cout << "Delete previous Queue" << endl;
				deleteQueue(begin);
			}
			switch (code)
			{
			case 1: fillQueue(begin, end, true);
				continue;
			case 2:
				if (begin)
				{
					fillQueue(begin, end);
				}
				else
				{
					cout << "There is no queue! Created new" << endl;
					fillQueue(begin, end, true);
				}
				continue;
			}
			break;
		case 3:
		case 4:
			if (isCorrectTask(begin, max, max_number))
			{
				if (code == 3)
				{
					new_Queue = individualTask1(begin, new_Queue_end, max);
				}
				else
				{
					new_Queue = individualTask2(begin, new_Queue_end, max_number);
				}
				cout << "New Queue:" << endl;
				viewQueue(new_Queue, new_Queue_end, is_from_end);
				cout << "Old Queue:" << endl;
				viewQueue(begin, end, is_from_end);
			}
			else
			{
				cout << "Bad Queue, nothing interesting!" << endl;
			}
			break;
		case 5: viewQueue(begin, end, is_from_end);
			break;
		case 6:
			if (begin) deleteQueue(begin);
			if (new_Queue) deleteQueue(new_Queue);
			break;
		case 0:
			cout << "Safe exit..." << endl;
			if (begin) deleteQueue(begin);
			if (new_Queue) deleteQueue(new_Queue);
			system("pause");
			return 0;
		}
	}
}

void fillQueue(Queue*& begin, Queue*& end, bool is_new)
{
	int n, number, code, temp, i = 0;
	bool is_start = true;
	bool is_random = false;
	do
	{
		cout << "How do you want to fill Queue? \n By random - 1\n By keyboard - 2\n";
		temp = correctInputInt();
	} while (temp < 1 || temp > 2);
	if (temp == 1)
	{
		is_random = true;
	}
	do
	{
		cout << "How do you want to fill the queue? \n From the start - 1\n From the end - 2\n";
		code = correctInputInt();
	} while (code < 1 || code > 2);
	if (code == 2)
	{
		is_start = false;
	}
	do
	{
		cout << "How many?" << endl;
		n = correctInputInt();
	} while (n < 1);
	if (is_random)
	{
		int min, max;
		srand(time(NULL));
		cout << "What range? Enter min:" << endl;
		min = correctInputInt();
		cout << "Enter max:" << endl;
		max = correctInputInt();
		if (min > max)
		{
			cout << "Min > Max, swap them!" << endl;
			int temp;
			temp = min;
			min = max;
			max = temp;
		}
		if (is_new)
		{
			number = rand() % (max - min + 1) + min;
			createQueue(begin, end, number);
			i++;
		}
		for (i; i < n; i++)
		{
			number = rand() % (max - min + 1) + min;
			pushQueue(begin, end, number, is_start);
		}
	}
	else
	{
		if (is_new)
		{
			cout << "Enter number: " << endl;
			number = correctInputInt();
			createQueue(begin, end, number);
			i++;
		}
		for (i; i < n; i++)
		{
			cout << "Enter number: " << endl;
			number = correctInputInt();
			pushQueue(begin, end, number, is_start);
		}
	}
}

void createQueue(Queue*& begin, Queue*& end, int number)
{
	Queue* temp = new Queue;
	temp->number = number;
	temp->next = temp->prev = NULL;
	begin = temp;
	end = temp;
}

Queue* individualTask1(Queue*& begin, Queue*& end, Queue*& max)
{
	Queue* new_Queue = NULL;
	Queue* temp = begin->next;
	int variable, code;
	bool first = true;
	bool is_start = true;
	do
	{
		cout << "How do you want to sort the queue? \n From the start - 1\n From the end - 2\n";
		code = correctInputInt();
	} while (code < 1 || code > 2);
	if (code == 2)
	{
		is_start = false;
	}
	while (temp != max)
	{
		variable = popQueue(temp, end);
		if (first)
		{
			createQueue(new_Queue, end, variable);
			first = false;
		}
		else
		{
			pushQueue(new_Queue, end, variable, is_start);
		}
	}
	return new_Queue;
}

Queue* individualTask2(Queue*& begin, Queue*& end, int& max_number)
{
	Queue* new_Queue = NULL;
	Queue* temp = begin->next;
	int variable, code;
	bool first = true;
	bool is_start = true;
	do
	{
		cout << "How do you want to sort the queue? \n From the start - 1\n From the end - 2\n";
		code = correctInputInt();
	} while (code < 1 || code > 2);
	if (code == 2)
	{
		is_start = false;
	}
	while (temp->number < max_number)
	{
		variable = popQueue(temp, end);
		if (first)
		{
			createQueue(new_Queue, end, variable);
			first = false;
		}
		else
		{
			pushQueue(new_Queue, end, variable, is_start);
		}
	}
	return new_Queue;
}

bool isCorrectTask(Queue*& begin, Queue*& max, int& max_number)
{
	if (begin == NULL)
	{
		return false;
	}
	Queue* temp = (begin)->next;
	max = begin;
	int i = 0;
	while (temp)
	{
		if (max->number < temp->number)
		{
			max = temp;
		}
		temp = temp->next;
		i++;
	}
	max_number = max->number;
	cout << "MAX " << max_number << endl;
	if (max == begin || max == begin->next || i < 3)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void pushQueue(Queue*& begin, Queue*& end, int number, bool is_start)
{
	Queue* temp = new Queue;
	temp->number = number;
	if (is_start)
	{
		temp->prev = NULL;//впереди нет
		temp->next = begin;//сзади есть
		begin->prev = temp;
		begin = temp;
	}
	else
	{
		temp->next = NULL;//сзади нет
		temp->prev = end;//впереди есть
		end->next = temp;
		end = temp;
	}
}

int popQueue(Queue*& begin, Queue*& end)//по адресу
{
	int out;
	out = begin->number;
	if (begin != end)
	{
		Queue* temp = begin;
		(begin->next)->prev = begin->prev;
		begin = (begin->prev)->next = begin->next;
		delete temp;
	}
	else
	{
		Queue* temp = end;
		end = end->prev;
		end->next = NULL;
		delete temp;
	}
	return out;
}

Queue* viewQueue(Queue* begin, Queue* end, bool is_from_end)
{
	if (is_from_end)
	{
		if (end)
		{
			cout << end->number << '\t';
			end = end->prev;
			return viewQueue(begin, end, is_from_end);
		}
	}
	else
	{
		if (begin)
		{
			cout << begin->number << '\t';
			begin = begin->next;
			return viewQueue(begin, end, is_from_end);
		}

	}
	cout << endl;
	return begin;
}

void deleteQueue(Queue*& begin)//по адресу
{
	Queue* temp;
	while (begin)
	{
		temp = begin;
		begin = begin->next;
		delete temp;
	}
	cout << "Queue deleted succesfully" << endl;
}

int correctInputInt()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, please write INT numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}
