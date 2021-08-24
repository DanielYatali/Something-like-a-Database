/*
Purpose: This program reads the list of top 20 movies for the year 2020.
		 The program also reads each movie's:
			Name, Views per month for the year, rating(IMDb ratings) Description(IMDb descriptions) Genre and URL(You Tube).
		 	
		This program allows the user to select a variety of statistical calculations to be done on each/selected movie and by extension each month.
*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <cstring>
#include <windows.h>
#include <unistd.h>

using namespace std;


#define QUIT 12							// useful constant

//Function to display video
void showVideo (string URL) {
	char cURL [50];
	int i;

	for (i = 0; i < URL.length(); i=i+1){
    	cURL[i] = URL[i];
	}

	cURL[URL.length()] = '\0';
    
    ShellExecute(NULL, "open", cURL, NULL, NULL, SW_SHOWNORMAL);
}

//Function for Graph
void printStars (int numStars) {
    int i;

    for(i = 1; i<= numStars; i= i+1)
        cout << "*";

    cout << endl;
}


//Function to locate movie with the highest and lowest rating
void highest_rating(string movie[25], float rating[25], int count){
	float max= 0;
	float min = INT_MAX;
	int k = 0;
	string name_max , name_min;
	
	for(int i = 0; i < count; i++){
		if(rating[i] > max){
			max = rating[i];
			name_max = movie[i];
		}
		if(rating[i] < min){
			min = rating[i];
			name_min = movie[i];
		}
	}
	
	//Checking for duplicate highest rating
	cout<<"This highest rating was found on movie|s|: ";
	for(k = 0;k<count; k++){
		if(rating[k] == max){
			cout<<movie[k]<<",";
			
		}
	}
	
	//Checking for duplicate lowest rating
	cout<<" with rating "<<max<<" ";
	cout<<"\nThe lowest rating was found on movie|s|: ";
	for(k = 0; k<count;k++){
		if(rating[k] == min){
			cout<<movie[k]<<",";
			
		}
	}
	cout<<" with rating "<<min;
}

//Search a specific Genre
void genre_search(string movie[], string type[],string input,int count){
	int counter = 0;
	bool present = false;
	
	cout<<"\nThere are ";
	for(int i = 0;i < count; i++){
		if(type[i] == input){
			present = true;
			counter++;
		}
	}
	if(present){
		cout<<counter<<" movies with genre "<<input<<":\n";
	
		for(int i = 0;i < count; i++){
			if(type[i] == input){
				cout<<movie[i]<<"\n";
			}
		}
	}
	else
		cout<<"No movies with genre "<<input<<" in the Top 20 list\n";

}

//Fuction for Calculating Sum of views for a particular month and movie with the highest view for that month
void month_stats(int month[],string movie[],string month_name[],int input,int count){
	int max_year = 0;
	int max = 0;
	int sum = 0;
	string name;
	
	cout<<"Satistics for the month "<<month_name[input-1];
	cout<<"\nTotal views ";
	for(int i = 0; i<count;i++){
		sum += month[i];
		if(month[i]>max){
			max = month[i];
			name = movie[i];
		}
	}
	cout<<sum;
	cout<<"\nHighest views was "<<max<<" and was optained by "<<name;
	
}

//Menu Function

int menu () {

	int choice;
	bool validChoice;
	
	validChoice = false;
	
	while (!validChoice) {
		cout << "  COMP 1601 - Two-Day Assessment: Final Program" << endl;
		cout << "  ================================================" << endl;
		cout << endl;
		cout << "                   M E N U" << endl;
		cout << endl;
		cout << "  1.  Which movie had the highest and the lowest rating?" << endl;
		cout << "  2.  Search for movies with a specific genre. " << endl;
		cout << "  3.  Movies with views over N for a particular month." << endl;
		cout << "  4.  Which movie was viewed/rated more than another throughout the year?" << endl;
		cout << "  5.  Check for Consecutives Spikes in views for a Particular movie." << endl;
		cout << "  6.  Month statistics(Sum, Highest views for that month)." << endl;
		cout << "  7.  Generate a graph showing total views for each movie throughout the year." << endl;
		cout << "  8.  Update Data in an array." << endl;
		cout << "  9.  Add Data to an array." << endl;
		cout << "  10. Save data to a file." << endl;
		cout << "  11. Surprise Feature." << endl;
		cout << "  12. Quit." << endl;
		cout << endl;
		cout << "  Please choose an option or " << QUIT << " to quit: ";
		cin  >> choice;
	
		if (choice >= 1 && choice <= QUIT)	// QUIT is a constant; its use is optional.
			validChoice = true;
		else
			system("cls");					// useful way to clear the screen. Works on Windows only.
	}								
	
	return choice;
}

int main () {
	long long treshold;
	int views[250], month, index1, index2, num_views = 0, count = 1;
	int i = 0, k = 0, n = 12, response ,total_views[25] = {0}, total = 0, month_views;
	int jan[25],feb[25],march[25],april[25],may[25],june[25],july[25],aug[25],sep[25],oct[25],nov[25],dec[25];
	char input;
	float change, rating[25];
	bool present = false;
	string descript[25], title_movie[25], url[25], type[25], input_type;
	
	string months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};// array storing names of each month
	
	ifstream movie_file,description_file,url_file,rating_file, type_file,views_file;
	ofstream output_file;
	
	output_file.open("output.txt");
	movie_file.open("movies.txt");
	description_file.open("description.txt");
	url_file.open("URL.txt");
	rating_file.open("rating.txt");
	type_file.open("types.txt");
	views_file.open("views.txt");
	
	
	//Checking if file is open
	if(!movie_file.is_open() || !description_file.is_open() || !url_file.is_open() || !rating_file.is_open() || !type_file.is_open() || !views_file.is_open()){
    	cout<<"Error opening input file. Aborting...";
    	cout<<"\nEnsure that input files are in the same directory as the Cpp.";
    	return 1; // returning 1 to notify the user that program did not run as intented
    }
    
    
    cout<<"Reading Data from files into arrays";
	sleep(2);
	cout<<".";
	sleep(2);
	cout<<".";
	sleep(2);
	cout<<".";
	sleep(1);
	
    //Reading Data from files
    getline(url_file,url[0]);
    getline(movie_file, title_movie[0]);
    type_file>>type[0];
    getline(description_file, descript[0]);
	rating_file>>rating[0];
  
  	while(!type_file.eof()){
	    getline(url_file,url[count]);
	    getline(movie_file, title_movie[count]);
	    type_file>>type[count];
	    rating_file>>rating[count];
	    getline(description_file,descript[count]);
	    count +=1;
	  }
	 
	//Reading views in a separate loop as it contains the views for each month for each movie. Totaling to 240 elments as (20(movies)x12(months)) 
	views_file>>views[0];
	while(views[num_views] != -1){
		num_views++;
			views_file>>views[num_views];
	}
	
	//Finding to sum of all 12 months for each movie and placing them in an arrays
	for(i = 0;i<count;i++){
		for(k;k<n;k++){
			total_views[i] += views[k];//total views for each movie(12 values)
		}
		n = n + 12;	//the value of n is now changed to allow the addition of the next 12 values to be stored in the next array element i.
	}
	
	//Places views for each month in its respective arrays
	//These types of incrementation were necessary due to the manner in which data was stored within the file to the array views.
	//See document for a more indept view of how data was stored in files.
	
	k = 0;
	for(i = 0;i<num_views;i = k*12){
		jan[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 1;i<num_views;i = k*12+1){
		feb[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 2;i<num_views;i = k*12+2){
		march[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 3;i<num_views;i = k*12+3){
		april[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 4;i<num_views;i = k*12+4){
		may[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 5;i<num_views;i = k*12+5){
		june[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 6;i<num_views;i = k*12+6){
		july[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 7;i<num_views;i = k*12+7){
		aug[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 8;i<num_views;i = k*12+8){
		sep[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 9;i<num_views;i = k*12+9){
		oct[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 10;i<num_views;i = k*12+10){
		nov[k] = views[i];
		k++;	
	}
	k = 0;
	for(i = 11;i<num_views;i = k*12+11){
		dec[k] = views[i];
		k++;	
	}

	cout<<"\n\nData successfully Read to arrays...";
	sleep(2);
	cout<<"\n\nAll arrays has "<<count<<" elements stored within them except views array which has "<<num_views<<" elements\n";
	cout<<"\nPlease Press any key to launch menu\n";
	system("pause");
	system("cls");
	
	response = menu();
	while(response>0 && response< QUIT){
		
		//Checking for Response values
		if(response == 1){
			highest_rating(title_movie,rating,count);
		}
		
		if(response == 2){
			cout<<"Which genre would you like to search\nPlease use all lowercase letter example: action, adventure\nGenre == ";
			cin>>input_type;
			genre_search(title_movie,type,input_type,count);
		}
		
		if(response == 3){
			cout<<"\nPlease enter a value for N(p.s choose a large value as views are very large)\nfollowed by a month(1 to 12):\n";
			cout<<"Enter N == ";
			cin>>treshold;
			while(treshold>INT_MAX || treshold<1){
				cout<<"Number "<<treshold<<" cannot be processed\nPlease try again\nEnter N == ";
				cin>>treshold;
			}
			cout<<"Enter Month == ";
			cin>>month;
			while(month>12 || month<1){
				cout<<"Invalid month please try again/nEnter Month == ";
				cin>>month;
			}
			cout<<"\n";
			
			//Identifing which month was requested
			if(month == 1){
				//Checking for values in requested month that exceeded N.
				for(i = 0;i<count;i++){
					if(jan[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed:"<<jan[i]<<" times in january\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of january";
				}
			}
			present = false;
			if(month == 2){
				for(i = 0;i<count;i++){
					if(feb[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed:"<<feb[i]<<" times in february\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of february";
				}
			}
			present = false;
			if(month == 3){
				for(i = 0;i<count;i++){
					if(march[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed:"<<march[i]<<" times in march\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of march";
				}
			}
			present = false;
			if(month == 4){
				for(i = 0;i<count;i++){
					if(april[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<april[i]<<" times in april\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of april";
				}
			}
			present = false;
			if(month == 5){
				for(i = 0;i<count;i++){
					if(may[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<may[i]<<" times in may\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of may";
				}
			}
			present = false;
			if(month == 6){
				for(i = 0;i<count;i++){
					if(june[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<june[i]<<" times in june\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of june";
				}
			}
			present = false;
			if(month == 7){
				for(i = 0;i<count;i++){
					if(july[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<july[i]<<" times in july\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of july";
				}
			}
			present = false;
			if(month == 8){
				for(i = 0;i<count;i++){
					if(aug[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<aug[i]<<" in "<<month<<" times in august\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of august\n";
				}
			}
			present = false;
			if(month == 9){
				for(i = 0;i<count;i++){
					if(sep[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<sep[i]<<" times in september\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of september";
				}
			}
			present = false;
			if(month == 10){
				for(i = 0;i<count;i++){
					if(oct[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<oct[i]<<" times in october\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of october";
				}
			}
			present = false;
			if(month == 11){
				for(i = 0;i<count;i++){
					if(nov[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<nov[i]<<" times in novmeber\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of november";
				}
			}
			present = false;
			if(month == 12){
				for(i = 0;i<count;i++){
					if(dec[i]>treshold){
						present = true;
						cout<<title_movie[i]<<" was viewed: "<<dec[i]<<" times in december\n";
					}
				}
				if(present == false){
					cout<<"Sorry there were no movies that was viewed more than "<<treshold<<" in the month of december";
				}
			}
		}
		if(response == 4){
			cout<<"Please choose two movies you wish to compare.\n";
			cout<<"Here is a list of movies in our database: \n\n";
			
			//Displaying Movie Database
			for(i = 0; i<count;i++){
				cout<<i<<". "<<title_movie[i]<<"\n";
			}
			
			cout<<"\nPlease indicate by selected a number for each movie you wish to compare: ";
			cin>>index1>>index2;
			
			//Ensuring that user entered a valid index
			while(index1<0 || index1>count || index2 >count || index2 <0){
				cout<<"You have entered an invalid input please try again,re-enter both movie indexes: ";
				cin>>index1>>index2;
			}
			
			cout<<"\n\nDo you wish to compare rating(r) or views(v):\nPlease indicate by chooseing r or v: ";
			cin>>input;
			
			//Checking for valid input
			while(input != 'r' && input != 'v'){
				cout<<"\nPlease enter a value number "<<input<<" is not valid. input: ";
				cin>>input;
			}
			
			if(input == 'v' || input == 'V'){
			
				if(total_views[index1]>total_views[index2]){
					cout<<title_movie[index1]<<" was viewed "<<total_views[index1]-total_views[index2]<<" more times than "<<title_movie[index2]<<" in 2020";
				}
				else if(total_views[index1]<total_views[index2])
					cout<<title_movie[index2]<<" was viewed "<<total_views[index2]-total_views[index1]<<" more times than "<<title_movie[index1]<<" in 2020";
				
				else
					cout<<title_movie[index1]<<" and "<<title_movie[index2]<<" has the same total views: "<<total_views[index1];
				}
				
				
			else if(input == 'r' || input == 'R'){
				if(rating[index1]>rating[index2]){
				cout<<title_movie[index1]<<" was rated "<<rating[index1]-rating[index2]<<" more than "<<title_movie[index2]<<" in 2020";
				}
				else if(rating[index1]<rating[index2])
					cout<<title_movie[index2]<<" was rated "<<rating[index2]-rating[index1]<<" more than "<<title_movie[index1]<<" in 2020";
				else
					cout<<title_movie[index1]<<" and "<<title_movie[index2]<<" has the same rating: "<<rating[index1];
			}
			
	
		}
		
		if(response == 5){
			cout<<"Here is a list of movies in our database:\n";
			
			//Displaying Movie Database
			for(i = 0;i<count;i++){
				cout<<i<<". "<<title_movie[i]<<"\n";
			}
			
			cout<<"Please select the movie you would like to check for consecutive spikes by indication of interger: ";
			cin>>index1;
			
			while(index1>count-1 || index1<0){
				cout<<"Invalid index 0 to "<<count-1<<" only\nPlease try again: ";
				cin>>index1;
			}
			
			//Comparing views for movie in consecutives months to locate spikes
			
			present = false;
			if(jan[index1]<feb[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<feb[index1] - jan[index1]<<" views between the months of "<<months[0]<<" and "<<months[1]<<"\n";
				present = true;
				}
				
			if(feb[index1]<march[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<march[index1] - feb[index1]<<" views between the months of "<<months[1]<<" and "<<months[2]<<"\n";
				present = true;
				}
				
			if(march[index1]<april[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<april[index1] - march[index1]<<" views between the months of "<<months[2]<<" and "<<months[3]<<"\n";
				present = true;
				}
				
			if(april[index1]<may[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<may[index1] - april[index1]<<" views between the months of "<<months[3]<<" and "<<months[4]<<"\n";
				present = true;
				}
				
			if(may[index1]<june[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<june[index1] - may[index1]<<" views between the months of "<<months[4]<<" and "<<months[5]<<"\n";
				present = true;
				}
				
			if(june[index1]<july[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<july[index1] - june[index1]<<" views between the months of "<<months[5]<<" and "<<months[6]<<"\n";
				present = true;
				}
				
			if(july[index1]<aug[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<aug[index1] - july[index1]<<" views between the months of "<<months[6]<<" and "<<months[7]<<"\n";
				present = true;
				}
				
			if(aug[index1]<sep[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<sep[index1] - aug[index1]<<" views between the months of "<<months[7]<<" and "<<months[8]<<"\n";
				present = true;
				}
				
			if(sep[index1]<oct[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<oct[index1] - sep[index1]<<" views between the months of "<<months[8]<<" and "<<months[9]<<"\n";
				present = true;
				}
				
			if(oct[index1]<nov[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<nov[index1] - oct[index1]<<" views between the months of "<<months[9]<<" and "<<months[10]<<"\n";
				present = true;
				}
				
			if(nov[index1]<dec[index1]){
				cout<<title_movie[index1]<<" Had a spike of "<<dec[index1] - nov[index1]<<" views between the months of "<<months[10]<<" and "<<months[11]<<"\n";
				present = true;
				}
			
			//Check if present equals false, signaling that there wasn't any spikes.	
			if(!present){
				cout<<title_movie[index1]<<" had no consecutive month spikes for the year 2020\n";
			}
			
		}
		
		
		if(response == 6){
			cout<<"Select the month you would like to view via the interger indexes-(1,2,3,4,5,6,7,8,9,10,11,12: ";
			cin>>month;
			
			//Checking for valid input
			
			while(month>12 || month<1){
				cout<<"Please enter a valid month(interger): ";
				cin>>month;
			}
			
			//Locating which month was requested
			
			if(month == 1){
				month_stats(jan,title_movie,months,month,count);
			}
			
			else if(month == 2){
				month_stats(feb,title_movie,months,month,count);
			}
			
			else if(month == 3){
				month_stats(march,title_movie,months,month,count);
			}
			
			else if(month == 4){
				month_stats(april,title_movie,months,month,count);
			}
			
			else if(month == 5){
				month_stats(may,title_movie,months,month,count);
			}
			
			else if(month == 6){
				month_stats(june,title_movie,months,month,count);
			}
			
			else if(month == 7){
				month_stats(july,title_movie,months,month,count);
			}
			
			else if(month == 8){
				month_stats(aug,title_movie,months,month,count);
			}
			
			else if(month == 9){
				month_stats(sep,title_movie,months,month,count);
			}
			
			else if(month == 10){
				month_stats(oct,title_movie,months,month,count);
			}
			
			else if(month == 11){
				month_stats(nov,title_movie,months,month,count);
			}
			
			else if(month == 12){
				month_stats(dec,title_movie,months,month,count);
			}
			
		}
		
		if(response == 7){
			cout<<"HISTOGRAM Displaying Total Views for Each Movie for the Year 2020\n1 star = 10,000,000 views\n\n";
			for(i = 0;i<count;i++){
				cout<<setw(35 - sizeof(title_movie[i]))<<title_movie[i]<<" ||";
				printStars(ceil(total_views[i]*1.0/10000000));
				
			}
		}
		
		if(response == 8){
			cout<<"\nHere is a list of movies in our database: \n\n";
		
			for(i = 0; i<count;i++){
				cout<<i<<". "<<title_movie[i]<<"\n";
			}
			cout<<"\nPlease select a movie you would like to change the rating of:\n";
			cout<<"\nPlease indicate by choosing an index number as displayed above: ";
			cin>>index1;
			while(index1>count || index1<0){
				cout<<"Invalid index please try again: ";
				cin>>index1;
			}
			cout<<"\nThe movie you have selected is "<<title_movie[index1]<<"\n"<<"It has a current rating of "<<rating[index1];
			cout<<"\n\nWhat rating would you like to change it too: ";
			cin>>change;
			
			rating[index1] = change;
			
			cout<<"\nYou can now re-enter the interger value(index) of the movie to verify that a change has occured: ";
			cin>>index2;
			
			while(index2>count || index2<0){
				cout<<"Invalid index please try again: ";
				cin>>index2;
			}
			cout<<"\n"<<title_movie[index2]<<" has a new rating of "<<rating[index2];
			
		}
		
		if(response == 9){
			cout<<"If you wish to add a new movie you will also have to enter its:\nGenre,views(each month),description,rating and url to trailer: ";
			cout<<"\nMovie Name: ";
			cin>>title_movie[count];
			cout<<"Genre(single(1) genre): ";
			cin>>type[count];
			cout<<"Rating: ";
			cin>>rating[count];
			
			while(rating[count]>10 || rating[count]<0){
				cout<<"You have entered an invalid rating, ratings can be 0 to 10 only\nPlease re-enter the rating: ";
				cin>>rating[count];
			}
			
			cout<<"Please enter a link to the movie's trailer: ";
			cin>>url[count];
			cout<<"Views for each month(12):\n";
			
			//Entering views in respective month arrays
			for(i=0;i<12;i++){
				cout<<months[i]<<":  ";
				cin>>month_views;
				total += month_views;
				if(i==0){
					jan[count] = month_views;
				}
				else if(i == 1){
					feb[count] = month_views;
				}
				else if(i == 2){
					march[count] = month_views;
				}
				else if(i == 3){
					april[count] = month_views;
				}
				else if(i == 4){
					may[count] = month_views;
				}
				else if(i == 5){
					june[count] = month_views;
				}
				else if(i == 6){
					july[count] = month_views;
				}
				else if(i == 7){
					aug[count] = month_views;
				}
				else if(i == 8){
					sep[count] = month_views;
				}
				else if(i == 9){
					oct[count] = month_views;
				}
				else if(i == 10){
					nov[count] = month_views;
				}
				else if(i == 11){
					dec[count] = month_views;
				}
		
			}
			
			total_views[count] = total;
			cout<<"Please enter a breif description of the movie:\n";
			cout<<"Description: ";
			
			cin.ignore(); //ignoring the \n from the previous cin so getline would work
	
			getline(cin,descript[count]);//reading line entered by user
			
			count += 1; // new amount of elements in array
			
			system("cls");
			cout<<"Writing data to arrays";
			sleep(2);
			cout<<".";
			sleep(2);
			cout<<".";
			sleep(2);
			cout<<".";
			cout<<"\nThere are now "<<count<<" Movies in our database\n";
			sleep(3);
			cout<<"Here is the new list of movies in our database: \n";
			for(i=0;i<count;i++){
				cout<<i<<". "<<title_movie[i]<<"\n";
			}
		}
		
		if(response == 10){
			cout<<"Writing data from arrays to file output.txt";
			sleep(2);
			cout<<".";
			sleep(2);
			cout<<".";
			sleep(2);
			cout<<".\n";
			
			//The description and views for each month per months were not exported to the file due to the large amount of data it was.
			
			for(i=0;i<count;i++){
				output_file<<title_movie[i]<<"\nrating: "<<rating[i]<<"\ntotal views: "<<total_views[i]<<"\nurl: "<<url[i]<<"\n\n";
			}
			
		}
		
		if(response == 11){
			cout<<"Here is the new list of movies in our database: \n";
			for(i=0;i<count;i++){
				cout<<i<<". "<<title_movie[i]<<"\n";
			}
			
			cout<<"By use of the interger number select a movie you wish to know more about eg(0,1,2,3): ";
			cin>>index1;
			
			while(index1>count || index1<0){
				cout<<"invalid index try again: ";
				cin>>index1;
			}
			
			cout<<"Here is a breif description of "<<title_movie[index1]<<"\n\n";
			cout<<descript[index1];
			cout<<"\n\nWould you like to view the trailer of this movie (y/n): ";
			cin>>input;
			
			//Invalid input check
			while(input != 'y' && input !='n'){
				cout<<"Invalid input please try again: \n";
				cout<<"Would you like to view the trailer of this movie (y/n): ";
				cin>>input;
			}
			if(input == 'y'){
				showVideo(url[index1]);
			}
			
		}
		cout<<"\n\n\nPress any key to relauch the menu!";
		//Clearing and relaunching menu
		system("pause");
		system("cls");
		response = menu();
		
	}//End of while loop.
	
	cout<<"Program has ended successfully\n\nIf you saved data to a file please view the file output.txt for results.\n";
	cout<<"\nHave a great Day! ";
	
	
	return 0;
}



