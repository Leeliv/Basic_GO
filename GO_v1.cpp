#include <iostream>
#include <stdexcept>
#include <array>
#include <set>
#include <queue>

const int S = 9;
const int SS = S*S;
const char Empty = ' ', White = 'W', Black = 'B'; 

void Print_Board(std::array<char,SS>& Board){
 for(int x = 0; x < SS; x++){
   if (x % S == 0){
    std::cout << "\n";
   }
  std::cout << Board[x] << " ";
  }
 return;
}

char Switch_Player(char Current){
 if (Current == White){
  return Black;
 }
 else{
  return White; 
 }
}

std::array<int,4> Get_Neigbours(int CO){
 int left, right, top, bottom;
 std::array<int,4>Neigbours;

 if (CO % 9 != 0){
  left = CO - 1;
  Neigbours[0] = left;  
 }else{Neigbours[0] = -1;
  }

 if (CO % 9 != 8){
  right = CO + 1;
  Neigbours[1] = right;
 }else{Neigbours[1] = -1;
  }

 if (CO - 9 >= 0){
 top = CO - 9;
 Neigbours[2] = top;
 }else{Neigbours[2] = -1;
  }

 if (CO + 9 <= SS){
 bottom = CO + 9;
 Neigbours[3] = bottom;
 }else{Neigbours[3] = -1;
  }

 return Neigbours;
}

std::set<int> Potential_capture(std::array<char, SS>& Board, char Opp, int CO){
 std::queue<int> stoneQ;
 std::set<int> stoneS;
 
 int current;
 std::array<int, 4> currentNeigbours;

 stoneQ.push(CO);

 while(stoneQ.empty() != 1){
  current = stoneQ.front();
  stoneQ.pop();
  if (stoneS.find(current) == stoneS.end()){ // if current doesnt exists in set
   stoneS.insert(current);
   currentNeigbours = Get_Neigbours(current);
   std::cout << current << " CURRENT CAPTURE STONE \n NEIGBOURS \n";
   for (int neigbour : currentNeigbours){
    std::cout << neigbour << "\n";
    if (neigbour == -1){
     continue;
    }
    else if (Board[neigbour] != Opp && Board[neigbour] != Empty){
      continue;
    }
    else if (Board[neigbour] == Empty){
     stoneS.clear();
     std::cout << "CLEARING CAPTURE \n";
     return stoneS;
    }
    else{
      stoneQ.push(neigbour);
     }
   // std::cout << neigbour << " This is a Neigbour \n";
   }
  }else{
    continue;
   }
 }
 std::cout << "RETURNING CAP \n";

 for (int stone: stoneS){
  std::cout << stone << "\n";
 }
 
 return stoneS;

}


void Set_New_Board(std::array<char,SS>& Board){
 for(int x = 0; x < SS; x++){
  Board[x] = Empty;
}
}

bool Valid_Place(std::array<char,SS>& Board, int CO){
 
 if (CO < 0 || CO > SS){
  throw std::invalid_argument("Coordinate Not within board range.");
 }
 else if (Board[CO] != Empty){
  throw std::invalid_argument("This place is occupied dummy");
 }
 else{
  return true;
 }

}

void Place_Many(std::array<char, SS>& Board, char Type, std::set<int> Pieces){
 for(int Piece : Pieces){
  Board[Piece] = Type;
 }
 return;
}

bool Place(std::array<char,SS>& Board, char Player, int CO){
 try{
  Valid_Place(Board, CO);
 }
  catch(std::invalid_argument& e){
   std::cerr << e.what() << std::endl;
   return false;
  }

 std::array<int, 4>neigbours = Get_Neigbours(CO);
 std::array<char*,4>neigbours_ptr;
 for(int i = 0; i < 4; i++){
  if(neigbours[i] == -1){
   neigbours_ptr[i] = NULL;
  } 
  else{
   neigbours_ptr[i] = &Board[neigbours[i]];
  }
 }

 //POINTER TEST//
 std::cout << "Neigbour POINTER TEST \n";
 for(char* neib : neigbours_ptr){
  if(neib != NULL){
   std::cout << *neib << "\n";
  }
 }

 Board[CO] = Player; // Updated board with new placement
 char Opp = Switch_Player(Player);
 
 for (int i = 0; i < 4; i++){
  if (neigbours[i] == -1){
   continue;
  }
  else if (*neigbours_ptr[i] == Opp){
    std::set<int> test = Potential_capture(Board, Opp, neigbours[i]);
    Place_Many(Board, Empty, test);
    std::cout << "Printing capture\n";
    for (int piece : test){
     std::cout << piece << "\n";
    }
  }
 }
// std::set<int> test = Potential_capture(Board, Opp, CO);
 return true;
 }


/*void Place_Many(std::array<int, SS>& Board, char Type, std::set<int> Pieces){
 for(int Piece : Pieces){
  Board[Piece] = Type;
 }
 return;
}
*/

int main()
{
 bool InPlay = true;
 char Player = Black;
 std::array<char, SS> Board;
 int Cord;
 Set_New_Board(Board);
 //std::cout << Place(Board,White, 10) << " ";
 while (InPlay == true){
 std::cout << "place your next piece nerd \n";
 std::cin >> Cord;
 if (Place(Board,Player,Cord) == true){
  Print_Board(Board); 

 std::cout << "\n"; 
 Player = Switch_Player(Player);  
 }
}
}


