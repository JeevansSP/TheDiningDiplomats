#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class solution{
    public:
        vector<int> finalArrangement;
        bool foundArrangement;

        void findSeatingArrangement(vector<int> &table, int totalDiplomats, vector<bool> &isSeated, vector<vector<int>> &relationship){
            
            if(foundArrangement){ //pruning as to avoid unnecessary calls
                return;
            }
            else{
                
                if(table.size()==totalDiplomats){  //table has reached max limit hence needs to be checked if its valid             
                    
                    if(isValidArrangement(table, relationship)){ // if its valid we store it and switch the pruning boolean variable 
                        finalArrangement = table;
                        foundArrangement = true;
                        return;
                    }
                    return;
                    
                }
                else{
                        bool seatTheDiplomat = false; // this is used to determine if during iteration the diploamt can we seated in the current table or not based on the problem constraints
                        int tableSize = table.size();

                
                        for(int diplomatNumber=1; diplomatNumber<totalDiplomats; diplomatNumber++){

                            seatTheDiplomat = false;

                            if(foundArrangement) return; //pruning as to avoid unnecessary calls

                            if(isSeated[diplomatNumber]){
                                seatTheDiplomat = false;
                            }
                            // three conditions	(consider n as current table size)
                            // 1. if no one is left of n-2 diplomat then i can place friend of n-1 or indifferent right of n-1 and 
                            // 2. if there is a friend of n-2 left of n-2 then again i can place friend of n-1 or indifferent right of n-1 
                            // 3. if there is an indifferent diplomat left of n-2 then i should place a friend of n-1 right of n-1

                            else if(tableSize==2){
                                int leftDiplomatAndLeftNeighborRelationship = relationship[table[tableSize-1]][table[tableSize-2]];
                                int currentDiplomatAndLeftNeighborRelationship = relationship[diplomatNumber][table[tableSize-1]];

                                if(leftDiplomatAndLeftNeighborRelationship==-1 && currentDiplomatAndLeftNeighborRelationship==-1){
                                    seatTheDiplomat = false; // obviously cant have this 
                                }
                                else{
                                    seatTheDiplomat = true; //condition 1: this does not guarantee its valid hence will need to check once its reached full size if its valid or not
                                                            // example: dip1 foe2 foe3 dip4 ...... dipN
                                                            // size when placing foe3 dip was only 2, 
                                                            // we could not check the left neighbor of dip1  (lets call this checking condition 1)
                                }

                            }
                            else if ( tableSize>2 && relationship[table[tableSize-1]][table[tableSize-2]]==-1 ){
                                            
                                int leftLeftDiplomatAndLeftNeighborRelationship = relationship[table[tableSize-2]][table[tableSize-3]];
                                
                                int currentDiplomatAndLeftNeighborRelationship = relationship[diplomatNumber][table[tableSize-1]];

                                if(leftLeftDiplomatAndLeftNeighborRelationship==1){ 
                                    seatTheDiplomat = true; //condition 2: we know for sure this is valid
                                }
                                else if(leftLeftDiplomatAndLeftNeighborRelationship==0 && currentDiplomatAndLeftNeighborRelationship==1){ 
                                    seatTheDiplomat = true; //condition 3: we also know this will be valid
                                }
                                else{
                                    seatTheDiplomat = false;
                                }
                                
                                
                            }
                            else{
                                //there is one case where we do not know if its valid or not 
                                // example 1: dip1 dip2 ......  dipN-2 foeN-1 foeN
                                // We placed foeN thinking we can make a valid foe-foe seating arrangment in the next call but then we reach the max table size
                                //hence this will not guarantee a valid arrangement and will also need to checked when we reach max table size
                                // along with this  (lets call this checking conditon 2)
                                // example 2: foe1 dip2 dip3 ...... foeN
                                // this is another condition that needs to be checked when the table reaches max size (lets call this checking condition 3)
                                seatTheDiplomat = true; 
                            }

                            if(seatTheDiplomat){
                                table.push_back(diplomatNumber);
                                isSeated[diplomatNumber] = true;
                                findSeatingArrangement(table, totalDiplomats, isSeated, relationship);
                                table.pop_back();
                                isSeated[diplomatNumber] = false;
                            }
                        }
                        return;
                    }
            }
        }

    private:
               

        bool isValidArrangement(vector<int> &table, vector<vector<int>> &relationship){
            int tableSize = table.size();

            int lastAndFirstDiplomatRelationship = relationship[table[tableSize-1]][table[0]];

            if(lastAndFirstDiplomatRelationship!=-1){
                if(tableSize>=3){ 
                    int firstDiplomatAndRightNeighborRelationhsip = relationship[table[0]][table[1]];
                    int rightOfFirstDiplomatAndRightNeighborRelationship = relationship[table[1]][table[2]];
                    int lastDiplomatAndLeftNeighborRelationship = relationship[table[tableSize-1]][table[tableSize-2]];
                    int leftOfLastDiplomatAndLeftNeighbor = relationship[table[tableSize-2]][table[tableSize-3]];

                    // checking condition 1
                    if(firstDiplomatAndRightNeighborRelationhsip==-1 && !( (rightOfFirstDiplomatAndRightNeighborRelationship==1 && lastAndFirstDiplomatRelationship==1) || (rightOfFirstDiplomatAndRightNeighborRelationship==0 && lastAndFirstDiplomatRelationship==1) || (rightOfFirstDiplomatAndRightNeighborRelationship==1 && lastAndFirstDiplomatRelationship==0))){
                        return false;
                    }
                    //checking condition 2
                    if(lastDiplomatAndLeftNeighborRelationship==-1 && !( (leftOfLastDiplomatAndLeftNeighbor==1 && lastAndFirstDiplomatRelationship==1) && (leftOfLastDiplomatAndLeftNeighbor==1 && lastAndFirstDiplomatRelationship==0) && (leftOfLastDiplomatAndLeftNeighbor==0 && lastAndFirstDiplomatRelationship==1) )){
                        return false;
                    }
                }
                return true;
            } 

            if(tableSize==1){
                return true; //will not happen but jsut in case
            }
            else if(tableSize==2){
                return false; //as they cant have other non-foe neighbors
            }
            else{
                // checking condition 3
                int firstDiplomatAndRightNeighborRelationhsip = relationship[table[0]][table[1]];
                int lastDiplomatAndLeftNeighborRelationship = relationship[table[tableSize-1]][table[tableSize-2]];

                if( (firstDiplomatAndRightNeighborRelationhsip==1 && lastDiplomatAndLeftNeighborRelationship==1) || (firstDiplomatAndRightNeighborRelationhsip==0 && lastDiplomatAndLeftNeighborRelationship==1) || (firstDiplomatAndRightNeighborRelationhsip==1 && lastDiplomatAndLeftNeighborRelationship==0) ){
                    return true;
                }
            }
            return false;
        }
};


int main() {
    int count = 0;
    
    vector<string> rough;
    string roughInput;

    while(cin>>roughInput){
        rough.push_back(roughInput);
    }
    
    for(int i=0;i<rough.size();i++){
        if((rough[i]!="1" && rough[i]!="0")){
            string cleanedName;
            for(int j=0;j<rough[i].size(); j++){
                if(rough[i][j]>=65 && rough[i][j]<=90){ //lower case all the capitalised letters
                    cleanedName+=(rough[i][j]+('a'-'A'));
                }
                else if(rough[i][j]>=97 && rough[i][j]<=122){ //keep lower cased letters as is
                    cleanedName+=rough[i][j];
                }
                else{
                    //do not add to the cleaned name hence do nothing
                }
            }
            cleanedName[0]-=('a'-'A'); //first letter of the name needs to be capitalized;
            rough[i]=cleanedName;
        }
    }

    // convert the diploamats into numbers, for easier calculation and store in a map

    unordered_map<string, int> diplomatNumberMap;
    unordered_map<int, string> numberDiplomatMap;
    vector<string> sortedDiplomats; 
    int currentDiplomatNumber = 0;

    for(auto &roughInput : rough){
        if(roughInput != "1" && roughInput != "0"  && diplomatNumberMap.find(roughInput)==diplomatNumberMap.end()){
            diplomatNumberMap[roughInput] = currentDiplomatNumber;
            numberDiplomatMap[currentDiplomatNumber] = roughInput;
            sortedDiplomats.push_back(roughInput);
            ++currentDiplomatNumber;

        }
    }

    // sort all the unique diplomats stored 
    sort(sortedDiplomats.begin(), sortedDiplomats.end());

    int totalDiplomats = currentDiplomatNumber;

    vector<vector<int>> relationship(totalDiplomats, vector<int> (totalDiplomats,0));

    for(int i=0; i<rough.size(); i++){ //we know if in the input we find 1 or 0 then it will ALWAYS be preceeded by 2 names whose relationship is 1 or 0 
        if(rough[i]=="1" || rough[i]=="0"){
            int diplomat1 = diplomatNumberMap[rough[i-1]], diplomat2 = diplomatNumberMap[rough[i-2]], currentRelationship =0;

            if (rough[i]=="1") currentRelationship = 1;
            else currentRelationship = -1;

            relationship[diplomat1][diplomat2] = currentRelationship;
            relationship[diplomat2][diplomat1] = currentRelationship;

        }
    }

    vector<int> table={0}; //since its circular, we can chose any person as the first seated in the table
    vector<bool> isSeated(totalDiplomats, false);

    solution solve;
    solve.foundArrangement = false; //important, as this helps in pruning

    solve.findSeatingArrangement(table, totalDiplomats, isSeated,  relationship);

    cout<<"Diplomats: ";
    for(int i=0; i<sortedDiplomats.size(); i++){ //printing all the diplomats in sorted order
        cout<<sortedDiplomats[i];
        if(i<sortedDiplomats.size()-1) cout<<", ";
    }
    cout<<endl;

    cout<<"Seating Arrangement: ";
    if(solve.foundArrangement){ // printing the final result
        
        for(int i=0; i<solve.finalArrangement.size(); i++){
            cout<<numberDiplomatMap[solve.finalArrangement[i]];
            if(i<solve.finalArrangement.size()-1) cout<<", ";

        }
        cout<<endl;
    }
    else{
        cout<<"Unfortunately No valid seating arrangment could be found";
    }
    return 0;
}

