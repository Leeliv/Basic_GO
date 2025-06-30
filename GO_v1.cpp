#include <iostream>
#include <array>

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

void Set_New_Board(std::array<char,SS>& Board){
 for(int x = 0; x < SS; x++){
  Board[x] = Empty;
}
}

bool Valid_Place(std::array<char,SS>& Board, int CO){
 if (CO < 0 || CO > SS){
  return false;
 }
 else if (Board[CO] != Empty){
  return false;
 }
 else{
  return true;
 }

}

bool Place(std::array<char,SS>& Board, char Player, int CO){
 if (Valid_Place(Board, CO) == true){
  Board[CO] = Player;
  return true;
 }

}

void Place_Many(){
}

/*bool Valid_Place(std::array<char,SS>& Board, int CO){
 if (CO < 0 || CO > SS){
  return false;
 }
 else if (Board[CO] != Empty){
  return false;
 }
 else{
  return true;
 }

}*/

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
 Place(Board,Player,Cord);
 Print_Board(Board); 
 /*for(int x = 0; x < SS; x++){
  if (x % S == 0){
   std::cout << "\n";
  }
  
 std::cout << Board[x] << " ";
 }*/
std::cout << "\n"; 
Player = Switch_Player(Player);  
 
}
}

/* void SetBoard(std::array<char,SS>& Board){
 for(int x = 0; x < SS; x++){
  Board[x] = White;
}
} */


