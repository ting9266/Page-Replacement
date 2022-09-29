#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <queue>


using namespace std;


struct Data
{ 
    int reference ;
    int counter;
};


vector<int> datalist;
vector<int> fifolist;
vector<int> lrulist;
vector<Data> lfulrulist;
vector<Data> mfufifolist;
vector<Data> muflrulist;

string filename = "\0";

int spilt( string &line );
void readandAcc(string line);
int find(vector<int> list, int pid );
int findforcounter(vector<Data> list, int pid );
int findcountersmallest(vector<Data> list);
int findcounterbiggest(vector<Data> list);

void FIFO(int framenumber);
void LRU(int framenumber);
void LFULRU(int framenumber);
void MFUFIFO(int framenumber);
void MUFLRU(int framenumber);


int main(){
  fstream infile,outfile;
  int waynumber = 0, framenumber = 0 ;
  int linenumber = 0, time = 0  ;
  

  cout << "Input file name(input_...):\n" ;
  //filename = "input3";
  cin >> filename;

  while ( filename != "0") {

    //開檔案
    infile.open(filename + ".txt", ios::in);

    //輸入wayofnumber和framenumber
    string line = "/0";
    getline(infile, line);
    waynumber = spilt(line);
    framenumber =  spilt(line);
    //framenumber =  3;
    //cout << waynumber  << endl ;
    //cout << framenumber  << endl ;

    
    
    datalist.clear();
    fifolist.clear();
    lrulist.clear();
    lfulrulist.clear();
    mfufifolist.clear();
    muflrulist.clear();
    //cout<< datalist.size();
    
    //輸入資料
    while (getline(infile, line) ) {
        linenumber++;
        if( line.size() > 0 )
          readandAcc(line);
        //cout << line << endl ;   
    } // end while
    
    switch (waynumber) {
        case 1:{ //FIFO

            FIFO(framenumber);
            break;
        }
        case 2:{ //LRU
            
            LRU(framenumber);
            break;
        }
        case 3:{ //LFULRU
            
            LFULRU(framenumber);
            break;
        }
        case 4: { // MFUFIFO

            MFUFIFO(framenumber);
            break;
        }
        case 5: { // MUFLRU

            MUFLRU(framenumber);
            break;
        }
        case 6: { // ALL
            
            FIFO(framenumber);
           
            LRU(framenumber);
            
            LFULRU(framenumber);
            
            MFUFIFO(framenumber);
            
            MUFLRU(framenumber);
            
            break;
        }
        default:
            break;
    }  // end switch

   cout << "\n\nSuccessful!Check the output:"<< "out_"+filename + ".txt" << "\n";
    
   cout << "\n\nInput file name(input_...):\n";
   cin >> filename ;

   infile.close();
  }

  cin.get();

}



//*******************************************************************************//
//*                        STORE  INPUT DATA                                    *//
//*******************************************************************************//

int spilt( string &line ){
    int number = 0 ;
    int whitespace = 0, i = 0 ;
    stringstream ss;
    ss << line;
    ss >> number;

    while( i < line.size() ){
      if( line[i] == ' '){
         whitespace++; 
      } // if
      i++;
    }  //while
    line.erase(0,whitespace); //刪除wayofnumber及空格

    return number ;
}  // split()


void readandAcc(string line){
  for(int i = 0 ; i < line.size() ; i++ ){
    datalist.push_back( (int)line[i]-'0' );
    //cout<< datalist[i]<<endl;
  }//for
} // end readandAcc()


//*******************************************************************************//
//*                       Way of Page Replacement                               *//
//*******************************************************************************//

void FIFO(int framenumber){
  int pagefault = 0, pagereplacement = 0 ;
  bool fault = false ;

  fstream outfile;
  outfile.open( "out_"+filename + ".txt", ios::out  );
  outfile << "--------------FIFO-----------------------\n" ;
  
  for(int i = 0 ; i < datalist.size() ; i++ ){
    fault = false ;
    //cout << datalist[i] << "\t";
    outfile << datalist[i] << "	";
    
    if( find(fifolist,datalist[i]) == -1 ){
      pagefault++;
      fault = true ;
      fifolist.push_back(datalist[i]);
      if( fifolist.size() > framenumber ){
        fifolist.erase (fifolist.begin());
        pagereplacement++ ;
       }

    }

    for(int j = fifolist.size()-1 ; j >= 0 ; j-- ){
      //cout << fifolist[j] ;
      outfile << fifolist[j] ;
    }
    if(fault == true){
      //cout << "	F";
      outfile <<  "\tF";
    }
    //cout << endl;
    outfile << endl ;

  } //for

  //cout << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile.close();

}  // FIFO()

void LRU(int framenumber){
  int pagefault = 0, pagereplacement = 0 ;
  bool fault = false ;

  fstream outfile;
  outfile.open( "out_"+filename + ".txt", ios::out | ios::app );
  outfile << "--------------LRU-----------------------\n" ;
  
  for(int i = 0 ; i < datalist.size() ; i++ ){
    fault = false ;
    //cout << datalist[i] << "\t";
    outfile << datalist[i] << "	";
    
    if( find(lrulist,datalist[i]) == -1 ){
      pagefault++;
      fault = true ;
      lrulist.push_back(datalist[i]);
      if( lrulist.size() > framenumber ){
        lrulist.erase (lrulist.begin());
        pagereplacement++ ;
       }

    }
    else{
      lrulist.erase (lrulist.begin()+find(lrulist,datalist[i]));
      lrulist.push_back(datalist[i]);
    }

    for(int j = lrulist.size()-1 ; j >= 0 ; j-- ){
      //cout << lrulist[j] ;
      outfile << lrulist[j] ;
    }
    if(fault == true){
      //cout << "	F";
      outfile <<  "\tF";
    }
    //cout << endl;
    outfile << endl ;

  } //for

  //cout << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile.close();

} //LRU()

void LFULRU(int framenumber){
  int pagefault = 0, pagereplacement = 0 ;
  Data temp ;
  bool fault = false ;

  fstream outfile;
  outfile.open( "out_"+filename + ".txt", ios::out | ios::app );
  outfile << "--------------Least Frequently Used LRU Page Replacement-----------------------\n" ;
  
  for(int i = 0 ; i < datalist.size() ; i++ ){
    fault = false ;
    //cout << datalist[i] << "\t";
    outfile << datalist[i] << "	";
    
    if( findforcounter(lfulrulist,datalist[i]) == -1 ){
      pagefault++;
      fault = true ;
      temp.reference = datalist[i];
      temp.counter = 1 ;
      if( lfulrulist.size()+1 > framenumber ){
        lfulrulist.erase (lfulrulist.begin()+findcountersmallest(lfulrulist));
        pagereplacement++ ;
      }
      lfulrulist.push_back(temp);
      

    }
    else{
      temp.reference = datalist[i];
      temp.counter = lfulrulist[findforcounter(lfulrulist,datalist[i])].counter+1 ;
      lfulrulist.erase (lfulrulist.begin()+findforcounter(lfulrulist,datalist[i]));
      lfulrulist.push_back(temp);
    }

    for(int j = lfulrulist.size()-1 ; j >= 0 ; j-- ){
      //cout << lfulrulist[j].reference ;
      outfile << lfulrulist[j].reference ;
    }
    if(fault == true){
      //cout << "	F";
      outfile <<  "\tF";
    }
    //cout << endl;
    outfile << endl ;

  } //for

  //cout << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile.close();

} // LFULRU()
   
void MFUFIFO(int framenumber){
  int pagefault = 0, pagereplacement = 0 ;
  Data temp ;
  bool fault = false ;

  fstream outfile;
  outfile.open( "out_"+filename + ".txt", ios::out | ios::app );
  outfile << "--------------Most Frequently Used Page Replacement -----------------------\n";
  
  for(int i = 0 ; i < datalist.size() ; i++ ){
    fault = false ;
    //cout << datalist[i] << "\t";
    outfile << datalist[i] << "	";
    
    if( findforcounter(mfufifolist,datalist[i]) == -1 ){
      pagefault++;
      fault = true ;
      temp.reference = datalist[i];
      temp.counter = 1 ;
      mfufifolist.push_back(temp);
      if( mfufifolist.size() > framenumber ){
        mfufifolist.erase (mfufifolist.begin()+findcounterbiggest(mfufifolist));
        pagereplacement++ ;
      }

    }
    else{
      mfufifolist[findforcounter(mfufifolist,datalist[i])].counter ++ ;
      //cout << mfufifolist[findforcounter(mfufifolist,datalist[i])].reference << mfufifolist[findforcounter(mfufifolist,datalist[i])].counter << endl;
    }
    
    for(int j = mfufifolist.size()-1 ; j >= 0 ; j-- ){
      //cout << mfufifolist[j].reference ;
      outfile << mfufifolist[j].reference ;
    }
    if(fault == true){
      //cout << "	F";
      outfile <<  "\tF";
    }
    //cout << endl;
    outfile << endl ;

  } //for

  //cout << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile.close();


} // MFUFIFO()

void MUFLRU(int framenumber){
  int pagefault = 0, pagereplacement = 0 ;
  Data temp ;
  bool fault = false ;

  fstream outfile;
  outfile.open( "out_"+filename + ".txt", ios::out | ios::app );
  outfile << "--------------Most Frequently Used LRU Page Replacement -----------------------\n";
  
  for(int i = 0 ; i < datalist.size() ; i++ ){
    fault = false ;
    //cout << datalist[i] << "\t";
    outfile << datalist[i] << "	";
    
    if( findforcounter(muflrulist,datalist[i]) == -1 ){
      pagefault++;
      fault = true ;
      temp.reference = datalist[i];
      temp.counter = 1 ;
      muflrulist.push_back(temp);
      if( muflrulist.size() > framenumber ){
        muflrulist.erase (muflrulist.begin()+findcounterbiggest(muflrulist));
        pagereplacement++ ;
       }

    }
    else{
      temp.reference = datalist[i];
      temp.counter = muflrulist[findforcounter(muflrulist,datalist[i])].counter+1 ;
      muflrulist.erase (muflrulist.begin()+findforcounter(muflrulist,datalist[i]));
      muflrulist.push_back(temp);
    }
    for(int j = muflrulist.size()-1 ; j >= 0 ; j-- ){
      //cout << muflrulist[j].reference ;
      outfile << muflrulist[j].reference ;
    }
    if(fault == true){
      //cout << "	F";
      outfile <<  "\tF";
    }
    //cout << endl;
    outfile << endl ;

  } //for

  //cout << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl << endl;
  outfile << "Page Fault = " << pagefault <<  "  Page Replaces = " << pagereplacement << "  Page Frames = " << framenumber << endl ;
  outfile.close();

} // MUFLRU()


//*******************************************************************************//
//*                    help Page Replacement                                    *//
//*******************************************************************************//

int find(vector<int> list, int pid ){
  for(int i = 0 ; i < list.size(); i ++ ){
    if( list[i] == pid )
      return i;
  }
 
  return -1 ;
} // find()

int findforcounter(vector<Data> list, int pid ){
  for(int i = 0 ; i < list.size(); i ++ ){
    if( list[i].reference == pid )
      return i;
  }
 
  return -1 ;
} //findforcounter()

int findcountersmallest(vector<Data> list){
  int counter = 999 , position = 0 ;
  for(int i = 0 ; i < list.size(); i ++ ){
    if( list[i].counter < counter ){
      counter = list[i].counter;
      position = i ;
    }   
  }
  return position ;
} //  findcountersmallest()

int findcounterbiggest(vector<Data> list){
  int counter = 0 , position = 0 ;
  for(int i = 0 ; i < list.size(); i ++ ){
    if( list[i].counter > counter ){
      counter = list[i].counter;
      position = i ;
    }   
  }
  return position ;
} //  findcountersmallest()