#include <iostream>
#include <ctime>

using namespace std;

struct Queue
{
	int number;
	Queue* prev, * next;
};

void pushQueue(Queue*& begin, Queue*& end, int number, bool is_start = true);
Queue* viewQueue(Queue* begin);
Queue* individualTask1(Queue*& begin, Queue*& end, Queue*& max);
Queue* individualTask2(Queue*& begin, Queue*& end, int& max_number);
void createQueue(Queue*& begin, Queue*& end, int number);
void deleteQueue(Queue*& begin);
void fillQueue(Queue*& begin, Queue*& end, bool is_random = false, bool is_new = false);
bool isCorrectTask(Queue*& begin, Queue*& max, int& max_number);
int popQueue(Queue*& begin, Queue*& end);
int correctInputInt();

int main()
{
	Queue* begin = NULL, * end = NULL, * max = NULL, * new_Queue = NULL, *new_Queue_end = NULL;
	int max_number;
	while (true)
	{
		int code = 0;
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
			do
			{
				cout << "How you want to fill Queue? \n By random - 1\n By keyboard - 2\n";
				code = correctInputInt();
			} while (code < 1 || code > 2);
			switch (code)
			{
			case 1: fillQueue(begin, end, true, true);
				continue;
			case 2: fillQueue(begin, end);
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
				viewQueue(new_Queue);
				cout << "Old Queue:" << endl;
				viewQueue(begin);
			}
			else
			{
				cout << "Bad Queue, nothing interesting!" << endl;
			}
			break;
		case 5: viewQueue(begin);
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

void fillQueue(Queue*& begin, Queue*& end, bool is_random, bool is_new)
{
	int n, number, i = 0;
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
		for (i; i < n; i++)//?
		{
			number = rand() % (max - min + 1) + min;
			pushQueue(begin, end, number);
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
			pushQueue(begin, end, number);
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
	int variable;
	bool first = true;
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
			pushQueue(new_Queue, end, variable);
		}
	}
	return new_Queue;
}

Queue* individualTask2(Queue*& begin, Queue*& end, int& max_number)
{
	Queue* new_Queue = NULL;
	Queue* temp = begin->next;
	int variable;
	bool first = true;
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
			pushQueue(new_Queue, end, variable);
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

Queue* viewQueue(Queue* begin)
{
	if (begin)
	{
		cout << begin->number << "\t";
		begin = begin->next;
		return viewQueue(begin);
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
