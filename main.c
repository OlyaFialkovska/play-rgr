//logic chapter
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define highfield 4
#define widthfield 6
int field [highfield][widthfield];

void generation_fox()
{
    srand(time(NULL));
    int eight=0;
    for(int i=0; i<highfield; i++)
        for(int j=0; j<widthfield; j++)
            field[i][j]=0;//0
    while( eight<8 )
    {
        field [rand()%highfield][rand()%widthfield]+=1;
        eight++;
    }
    for(int i=0; i<highfield; i++)
    {
        for(int j=0; j<widthfield; j++)
            printf("%d\t",field[i][j]);
        printf("\n");
    }
}
void input_coordinates()
{
    int h,w;
    printf("Field %dx%d\n",highfield,widthfield);
    printf("Enter the coordinates of the fox:\n");
    while(1)
    {
        printf("height:\t");
        scanf("%d",&h);
        h-=1;
        if(h>=0 && h<highfield)
        {
            break;
        }
        else
        {
            printf("h>0 && h<%d\n",highfield);
            fflush (stdin);
        }

    }
    //system("cls");
    while(1)
    {
        printf("width:\t");
        scanf("%d",&w);
        w-=1;
        if(w>=0 && w<widthfield)
        {
            break;
        }
        else
        {
            printf("w>0 && w<%d\n",widthfield);
            fflush (stdin);
        }
    }
    // system("cls");
   // printf("height:\t%d\n",h);
    //printf("width:\t%d\n",w);
    switch( field [h][w] )
    {
    case 0:
        printf("fox not found\n");
        count_foxes(h,w);
        break;
    case 1:
        printf("fox found\n");
        count_foxes(h,w);
        break;
    default:
        printf("%d foxes found\n",field [h][w]);
        count_foxes(h,w);
        break;
    }
}
void count_foxes(int h,int w)
{

    int counter_1=0;
    printf("vertical:\t");
    for(int i=0; i<highfield; i++)
    {
        if(field [i][w]!=0 && i!=h)
            counter_1+=field [i][w];
    }
    printf("%d\n",counter_1);

    int counter_2=0;
    printf("horizontal:\t");
    for(int j=0; j<widthfield; j++)
    {
        if(field [h][j]!=0 && j!=w)
            counter_2+=field [h][j];
    }
    printf("%d\n",counter_2);

    int counter_3=0;
    printf("diagonal:\t");
    for(int i=h-1,j=w-1; i>=0 && j>=0; i--,j--)
        if(field [i][j]!=0 )//&& i!=h && j!=w
          //  printf(" 1=%d ",field [i][j]);
            counter_3+=field [i][i];

    for(int i=h+1,j=w+1; i<highfield && j<widthfield; i++,j++)
        if(field [i][j]!=0 )//&& i!=h && j!=w
           // printf(" 2=%d ",field [i][j]);
            counter_3+=field [i][i];

//diagonal
    for(int i=h-1,j=w+1; i>=0 && j<widthfield; i--, j++)
        if(field [i][j]!=0)
            //printf(" 3=%d ",field [i][j]);
            counter_3+=field [i][j];


    for(int i=h+1, j=w-1; i<highfield && j>=0; i++,j--)
        if(field [i][j]!=0)
            //printf(" 4=%d ",field [i][j]);
            counter_3+=field [i][j];
    printf("%d\n",counter_3);
}
int main()
{
    generation_fox();
    input_coordinates();

    return 0;
}
*/
//2 chapter
/*
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SFML/Graphics.h>
float scale = 1;

#include <SFML/Audio.h>

int main() {
    sfVideoMode screen = {1000, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(screen, "my", sfResize|sfClose, NULL);
    if (!window)
        return 1;

    sfRenderTexture* texture = sfRenderTexture_create(1000, 600, 0);
    sfRenderTexture_clear(texture, sfBlack);
    ///
    sfMusic* music = sfMusic_createFromFile("Ring03.wav");

    if (!music) {
        printf("Error loading music file\n");
        return 1;
    }

    sfMusic_play(music);
    ///



    // add picture formula
    sfTexture* formula_texture = sfTexture_createFromFile("pic.jpg", NULL);
    sfSprite* form_sp = sfSprite_create();
    sfSprite_setTexture(form_sp, formula_texture, sfTrue);
    sfVector2f form_pos = {550, 60};
    sfSprite_setPosition(form_sp, form_pos);
    sfRenderTexture_drawSprite(texture, form_sp, NULL);
    sfText* name = sfText_create();
    sfFont_createFromFile("calibri.ttf");
    sfText_setCharacterSize(name, 14);
    sfText_setString(name, "loshochek");

    ///
    // Ждем, пока музыка играет
    while (sfMusic_getStatus(music) == sfPlaying) {
        // Продолжаем выполнение программы
    }

    // Освобождаем ресурсы, связанные с объектом музыки
    sfMusic_destroy(music);

    return 0; // Возвращаем успешный код завершения программы
}*/
//chapter with music and picture

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>

#define ELEMENT_SIZE 80
#define ELEMENTS_PER_ROW 10
#define ELEMENTS_PER_COLUMN 5

int selected_picture_index = -1; // -1 for no selection

typedef struct {
    sfVector2f position;
    sfTexture* texture;
    sfSprite* sprite;
} MiniPicture;

void minipictures(sfRenderTexture* texture, MiniPicture pictures[]) {
    // Load mini-picture textures
    for (int i = 0; i < ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN; i++) {
        pictures[i].texture = sfTexture_createFromFile("png-pikselnaya-trava60x60.png", NULL);
        if (!pictures[i].texture) {
            printf("Error loading picture texture\n");
            exit(1);
        }
        pictures[i].sprite = sfSprite_create();
        sfSprite_setTexture(pictures[i].sprite, pictures[i].texture, sfTrue);
    }

    // Fill array with mini-picture positions
    int index = 0;
    for (int row = 0; row < ELEMENTS_PER_COLUMN; row++) {
        for (int col = 0; col < ELEMENTS_PER_ROW; col++) {
            pictures[index].position.x = col * ELEMENT_SIZE + 12; // with padding
            pictures[index].position.y = row * ELEMENT_SIZE + 12; // with padding
            index++;
        }
    }

    // Draw each mini-picture at corresponding positions
    for (int i = 0; i < ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN; i++) {
        sfSprite_setPosition(pictures[i].sprite, pictures[i].position);
        sfRenderTexture_drawSprite(texture, pictures[i].sprite, NULL);
    }
}

void pop_up_window(sfRectangleShape* popup, sfText* text, sfRectangleShape* closeButton, sfFont* font) {
    // Создание прямоугольника для всплывающего окна
    sfVector2f popupSize = {400, 300};
    sfVector2f popupPosition = {200, 150};
    sfRectangleShape_setSize(popup, popupSize);
    sfRectangleShape_setPosition(popup, popupPosition);
    sfRectangleShape_setFillColor(popup, sfColor_fromRGBA(200, 200, 200, 255));

    // Создание текста
    sfText_setString(text, "This is a popup window!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfColor_fromRGB(0, 0, 0));
    sfVector2f textPosition = {220, 180};
    sfText_setPosition(text, textPosition);

    // Создание кнопки закрытия (крестик)
    sfVector2f buttonSize = {30, 30};
    sfVector2f buttonPosition = {560, 150};
    sfRectangleShape_setSize(closeButton, buttonSize);
    sfRectangleShape_setPosition(closeButton, buttonPosition);
    sfRectangleShape_setFillColor(closeButton, sfColor_fromRGB(255, 0, 0));
}

int main() {
    sfVideoMode screen = {1000, 900, 32};
    sfRenderWindow* window = sfRenderWindow_create(screen, "Graph", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfRenderTexture* texture = sfRenderTexture_create(1000, 600, 0);
    if (!texture)
        return 1;
    sfRenderTexture_clear(texture, sfBlack);

    // Load main picture texture
    sfTexture* formula_texture = sfTexture_createFromFile("grass_pic.png", NULL);
    if (!formula_texture) {
        printf("Error loading main picture texture\n");
        return 1;
    }

    // Load background picture texture with text
    sfTexture* background_texture = sfTexture_createFromFile("grass_1.jpg", NULL);
    if (!background_texture) {
        printf("Error loading background picture texture\n");
        return 1;
    }

    // Создание всплывающего окна
    sfRectangleShape* popup = sfRectangleShape_create();
    sfText* text = sfText_create();
    sfRectangleShape* closeButton = sfRectangleShape_create();
    sfFont* font = sfFont_createFromFile("calibri.ttf");
    pop_up_window(popup, text, closeButton, font);

    // Флаг для отображения всплывающего окна
    int showPopup = 0;

    sfSprite* form_sp = sfSprite_create();
    sfSprite_setTexture(form_sp, formula_texture, sfTrue);
    sfVector2f form_pos = {0, 0};
    sfSprite_setPosition(form_sp, form_pos);
    sfRenderTexture_drawSprite(texture, form_sp, NULL);

    // Load music
    sfMusic* music = sfMusic_createFromFile("plya.wav");
    if (!music) {
        printf("Error loading music file\n");
        return 1;
    }
    sfMusic_play(music);

    MiniPicture pictures[ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN];
    minipictures(texture, pictures);

    // Main event loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
                    // Check if the close button in the popup window is clicked
                    sfFloatRect closeButtonBounds = sfRectangleShape_getGlobalBounds(closeButton);
                    if (showPopup && sfFloatRect_contains(&closeButtonBounds, mouse.x, mouse.y)) {
                        showPopup = 0; // Закрытие всплывающего окна
                    } else {
                        // Check click within each mini-picture area
                        for (int i = 0; i < ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN; i++) {
                            sfVector2f picture_pos = pictures[i].position;
                            if (mouse.x >= picture_pos.x && mouse.x <= picture_pos.x + ELEMENT_SIZE &&
                                mouse.y >= picture_pos.y && mouse.y <= picture_pos.y + ELEMENT_SIZE) {
                                selected_picture_index = i;
                                // Здесь вы можете заменить текущую картинку на другую
                                sfTexture_destroy(pictures[i].texture); // Удаляем текущую текстуру
                                pictures[i].texture = sfTexture_createFromFile("fox60x60.png", NULL); // Загружаем новую текстуру
                                sfSprite_setTexture(pictures[i].sprite, pictures[i].texture, sfTrue); // Устанавливаем новую текстуру для спрайта
                                break; // Stop loop as picture is found
                            }
                        }
                    }
                }
            }
        }

        // Draw all mini-pictures considering the selected one
        sfRenderTexture_clear(texture, sfBlack);
        sfSprite_setPosition(form_sp, form_pos);
        sfRenderTexture_drawSprite(texture, form_sp, NULL); // Redraw the main picture
        for (int i = 0; i < ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN; i++) {
            sfRenderTexture_drawSprite(texture, pictures[i].sprite, NULL);
        }
        sfRenderTexture_display(texture);

        // Draw background picture with text
        sfRenderTexture* backgroundTexture = sfRenderTexture_create(1000, 2000, 100);
        sfRenderTexture_clear(backgroundTexture, sfBlack);
        sfSprite* backgroundSprite = sfSprite_create();
        sfSprite_setTexture(backgroundSprite, background_texture, sfTrue);
        sfRenderTexture_drawSprite(backgroundTexture, backgroundSprite, NULL);
        sfRenderTexture_drawText(backgroundTexture, text, NULL);
        sfRenderTexture_display(backgroundTexture);

        sfRenderWindow_clear(window, sfBlack);
        sfSprite* sp = sfSprite_create();
        sfSprite_setTexture(sp, sfRenderTexture_getTexture(texture), sfTrue);
        sfRenderWindow_drawSprite(window, sp, NULL);
        sfRenderWindow_drawSprite(window, sfSprite_create(), NULL); // Draw the background texture
        sfSprite_destroy(sp);

        if (showPopup) {
            sfRenderWindow_drawRectangleShape(window, popup, NULL);
            sfRenderWindow_drawText(window, text, NULL);
            sfRenderWindow_drawRectangleShape(window, closeButton, NULL);
        }

        sfRenderWindow_display(window);
    }

    // Free resources
    for (int i = 0; i < ELEMENTS_PER_ROW * ELEMENTS_PER_COLUMN; i++) {
        sfTexture_destroy(pictures[i].texture);
        sfSprite_destroy(pictures[i].sprite);
    }

    sfText_destroy(text);
    sfFont_destroy(font);
    sfRectangleShape_destroy(closeButton);
    sfRectangleShape_destroy(popup);

    sfTexture_destroy(formula_texture);
    sfSprite_destroy(form_sp);
    sfMusic_destroy(music);
    sfRenderTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return 0;
}




/*
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics/RectangleShape.h>

int main() {
    // Создание окна
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Popup Window", sfResize | sfClose, NULL);

    if (!window)
        return -1;

    // Загрузка изображения
    sfTexture* backgroundTexture = sfTexture_createFromFile("grass_pic.png", NULL);
    if (!backgroundTexture)
        return -1;
    sfSprite* backgroundSprite = sfSprite_create();
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);



    // Основной цикл программы
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);

            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyP) {
                    showPopup = 1; // Условие для отображения всплывающего окна
                }
            }

            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
                    sfFloatRect closeButtonBounds = sfRectangleShape_getGlobalBounds(closeButton);

                    if (sfFloatRect_contains(&closeButtonBounds, mousePos.x, mousePos.y)) {
                        showPopup = 0; // Закрытие всплывающего окна
                    }
                }
            }
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(255, 255, 255));
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);

        if (showPopup) {
            sfRenderWindow_drawRectangleShape(window, popup, NULL);
            sfRenderWindow_drawText(window, text, NULL);
            sfRenderWindow_drawRectangleShape(window, closeButton, NULL);
        }

        sfRenderWindow_display(window);
    }

    // Освобождение ресурсов
    sfText_destroy(text);
    sfFont_destroy(font);
    sfRectangleShape_destroy(closeButton);
    sfRectangleShape_destroy(popup);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
    sfRenderWindow_destroy(window);

    return 0;
}
*/
