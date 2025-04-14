#include "main.h"
#include "public.h"

void main()
{
    int language = ENGLISH;
    int gdriver = VGA;
    int gmode = VGAHI;
    int page = WELCOME;
    INFO *temp;
    DRONEINFO *drone;
    char pesticide[20] = {'\0'};
    char now_field[80] = {'\0'};
    initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");
    srand(time(0));

    while(1)
    { 

        switch(page)
        {
            case WELCOME :
               page = welcome_page(&language); //0
               break;

            case LOGIN :
               page = login_page(temp,language);//1
               break;

            case SIGNUP :
               page = signup_page(language);//2
               break;

            case HOME :
               page = home_page(temp,language);
               break;

            case FIELD :
               page = field_page(temp,now_field,language);
               break;

            case DRONE :
               page = drone_page(temp->name,drone->name,drone,language);
               break;

            case PESTICIDE :
               page = pesticide_page(temp->name,pesticide,language);
               break;

            case DETECTOR :
               page = detect_page(temp->name,now_field,language);
               break; 
            
            case DRAW_FIELD:
               page = draw_field_page(temp->name,now_field,language);
               break;

            case PLANT :
               page = plant_page(temp->name,now_field,language);
               break;
            
            case HOUSE :
               page = house_page(temp->name,now_field,language);
               break;
            
            case DRONE_LIST:
               page = drone_list_page(temp->name,drone,language);
               break;

            case README:
               page = language_page(&language);
               break;
            
			default :
				exit(1);
        }
    }
      getch();
      closegraph();
}
