// Semifinals Project for CSElec1 - Parallel and Distributed Computing
// Made by: Allan Oliver Polliente and Mj Estepanie Palo (BSCS 2A)

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>


using namespace std;

double Total_Lane_Queue_Time;

struct QueueCustomer {
	int itemNum;
	string pref_packaging;
	int num_packaging;
	string pref_payment;
	string Cash_type;
};

QueueCustomer extractData(string line)
{
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {""};
	int data_index = 0;

	while ((pos = line.find(delimiter)) != npos) {
	    data[data_index] = line.substr(0, pos);
	    line.erase(0, pos + delimiter.length());
	    data_index++;
	}
	data[data_index] = line;

	stringstream ss;

	QueueCustomer temp;

	for (int i = 0; i < 5; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2) {
			ss << d;
			if (i == 0) {
				ss >> temp.itemNum;
			} else if (i == 2) {
				ss >> temp.num_packaging;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.pref_packaging = d;
		} else if (i == 3) {
			temp.pref_payment = d;
		} else if (i == 4) {
			temp.Cash_type = d;
		}
	}
	return temp;
}

void print_input(QueueCustomer n, int index)
{

	float Total_Decarting_Time;
	float Total_Scanning_Time;
	float Total_Packing_Time;
	float Total_Paying_Time;
	float Total_Reciept_Printing_Time;
	int Idle_Time;
	float Total_Customer_Queue_Time;


	int cust_num;

	//Display the Inputs

	cust_num= index + 1;

	cout << "Customer #" << cust_num<< endl;
	cout << "No. of Cart Items: " << n.itemNum << endl;
	cout << "Preferred Packaging: " << n.pref_packaging << endl;
	cout << "Number of Box: " << n.num_packaging << endl;

	if(n.Cash_type == "e"){
		cout << "Preferred Payment Method: " << n.pref_payment << " (exact) " << endl;
	}
	else if(n.Cash_type == "ne"){
		cout << "Preferred Payment Method: " << n.pref_payment << " (not exact) " << endl;
	}
	else {
		cout << "Preferred Payment Method: " << n.pref_payment << endl;
	}

	cout << "------------------------------------------------\n";

	//Computes and Displays the Total Decarting Time
	Total_Decarting_Time = n.itemNum * 0.5;
	cout << "Total De-Carting Time: " <<  Total_Decarting_Time << endl;

	//Computes and Displays the Total Scanning Time
	Total_Scanning_Time =  n.itemNum * 0.5;
	cout << "Total Scanning Time: " <<  Total_Scanning_Time << endl;

	//Determines the Prefered Packaging
	//Computes and Displays the Total Packing Time
	if(n.pref_packaging == "box"){
		Total_Packing_Time = (n.itemNum * 0.50) + (n.num_packaging * 10);
		cout << "Total Packing Time: " <<  Total_Packing_Time << endl;
	}
	else if (n.pref_packaging == "bag") {
		Total_Packing_Time = (n.itemNum * 0.50) + (n.num_packaging * 5);
		cout << "Total Packing Time: " <<Total_Packing_Time << endl;
	}

	//Determines the Prefered Payment
	//If the Prefered Payment Method is Cash, Determines the whether exact or not exact payment
	//Displays The Total Paying Time
	if(n.pref_payment == "cash"){
		if(n.Cash_type == "e"){
			Total_Paying_Time = 15;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
		else if(n.Cash_type == "ne"){
			Total_Paying_Time = 20;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
	}
	if(n.pref_payment == "digital"){
		Total_Paying_Time = 15;
		cout << "Total Paying Time: " << Total_Paying_Time << endl;
	}

	//Computes and Display the Total Receipt Printing Time
	Total_Reciept_Printing_Time = (n.itemNum * 0.3) + 2;
	cout << "Total Receipt Printing Time: " << Total_Reciept_Printing_Time << endl;

	//Displays the Idle_Time
	if(index == 0){
		Idle_Time = 0;
		cout << "Idle Time: " <<  Idle_Time << endl;
	} else if(index > 0){
		Idle_Time = 3;
		cout << "Idle Time: " <<  Idle_Time << endl;
	}

	//Computes and Displays the Total Customer Queue Time
	Total_Customer_Queue_Time = Total_Decarting_Time + Total_Scanning_Time + Total_Packing_Time + Total_Paying_Time + Total_Reciept_Printing_Time + Idle_Time;
	cout << "Total Customer-Queue Time: " << Total_Customer_Queue_Time << endl;

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    Total_Lane_Queue_Time += Total_Customer_Queue_Time;



}


int main( )
{
	ifstream in_stream;

	in_stream.open("file.in");

	if(in_stream.fail())
    {
        cout<<"Input file opening failed.\n";
        exit(1);
    }

	int Number_Of_Customer;

	in_stream >> Number_Of_Customer;

	cout << "No. of Customers:: " << Number_Of_Customer << endl;
	cout << "================================================\n";

	QueueCustomer queue[Number_Of_Customer];

	QueueCustomer n;

	string line;

	int index = 0;

	while (getline(in_stream, line)) {
		if (line.length() > 0) {
			queue[index] = extractData(line);
			print_input(queue[index],index);
			index++;
		}
	}

    cout << "Total Lane Queue Time: " << Total_Lane_Queue_Time;

	return 0;
}
