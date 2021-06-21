//Template For patch.h. You can Edit This Too.

#include"patch.h" //Links The Patcher

int main() //Your Main Function
{
credit(); //My Credit Remove if you don't want to Give me :(
owner_name("Your Name"); //Your Name Goes Here
shell("echo HELLO WORLD");//New Shell Feature 
int get_pid; //Declaration of get_pid Variable
/*get_pid = check_game("com.package.name"); //Checks the game pid by package & Saves to get_pid variable.*/
get_pid = check_pubg(); //Use this If Your Target is PUBG Mobile GL ,KR , VN & TW . This Checks all Game at a Time & patches.
start_deamon(); //Starts Deamon
bypass_game(); //Bypass 3rd Party Detection
modify_base_type_QWORD(get_lib_base(get_pid, "libUE4.so") + 0xABC1234, 123456789900); //gets libbase By pid & Lib Name then it locates Address & Modifies Value.
print("Less Recoil Activated!"); //Shows The Success Message.
close(deamon); //Closes Deamon.

}
