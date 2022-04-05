
#include <stdlib.h>
#include <random>
#include "TXLib.h"




struct Switch
    {
    int x, y;
    int radius;

    };

struct ButtonType
    {
    char name[20];
    int x, y;
    COLORREF colortext;
    };



//Graphics

void Draw_switchDown    (int x, int y, int radius);
void Draw_switchUp      (int x, int y, int radius);
void Gradient();
int  ButtonCheckClickRound   (int x, int y, int radius, int mouse_x, int mouse_y);
void Print_array        (int array[]);
void Draw_Switch        (struct Switch Set[], int array[]);
void Draw_Lamps         (struct Switch Set[], int array[]);
void SwitchCheck        (struct Switch Set[], int array[]);
void Draw_Lamps         (struct Switch Lamps[], int array[], COLORREF from, COLORREF to, int time, int steps);
void Draw_Button        (struct ButtonType buttons[]);
void Title_Sort         (int x, int y, int size, int high, COLORREF color_title, char name[]);
int ButtonCheckClick    (int x, int y, int mouse_x, int mouse_y);

void Clear_Array        (int array []);
//Functions

int decoder(int array[]);
int pluss(int, int);
void zacoder(int array[], int);

int first_number[]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int second_number[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int lamp_set[]      = {0, 0, 0, 0, 0, 0, 0, 0, 0};

Switch Set1 [9] = {100, 190, 15,
                   160, 190, 15,
                   220, 190, 15,
                   280, 190, 15,
                   340, 190, 15,
                   400, 190, 15,
                   460, 190, 15,
                   520, 190, 15,
                   580, 190, 15,};

Switch Set2 [9] = {100, 280, 15,
                   160, 280, 15,
                   220, 280, 15,
                   280, 280, 15,
                   340, 280, 15,
                   400, 280, 15,
                   460, 280, 15,
                   520, 280, 15,
                   580, 280, 15,};

Switch Lamps[9] = {100, 380, 20,
                   160, 380, 20,
                   220, 380, 20,
                   280, 380, 20,
                   340, 380, 20,
                   400, 380, 20,
                   460, 380, 20,
                   520, 380, 20,
                   580, 380, 20,};

 ButtonType buttons[3] = {" CLEAR ",  60, 500, RGB(255, 128, 128),
                          " ADD ", 560, 500, RGB( 34, 145, 255),
                          "   EXIT ",  320, 500, RGB( 255, 145, 102),};





int main()
    {
    txCreateWindow (700, 600);
    HDC  Playing_field_View  = txLoadImage ("kotick.bmp");
    Gradient();
    Draw_Switch (Set1, first_number);
    Draw_Switch (Set2, second_number);
    Draw_Lamps  (Lamps, lamp_set, RGB(255, 255,0), RGB (255, 0, 20), 50, 13);
    Draw_Button (buttons);

    while(!txGetAsyncKeyState (VK_ESCAPE))
        {
        SwitchCheck (Set1, first_number);
        SwitchCheck (Set2, second_number);
        Draw_Lamps  (Lamps, lamp_set, RGB(255, 255,0), RGB (255, 0, 20), 50, 13);
        }

    txBitBlt  (txDC(), 0, 0, 700, 600, Playing_field_View, 0, 0);
    txDeleteDC (Playing_field_View);
    return 0;
    }


void Clear_Array (int array [])
    {
    for (int i = 0; i < 9; ++i)
        array[i] = 0;

    }

void Draw_Switch (struct Switch Set[], int array[])
    {

    for (int i = 0; i < 9; i ++)
        {
        if (array[i] == 1)
            {
            Draw_switchUp (Set[i].x, Set[i].y, Set[i].radius);
            }
        else
            {
            Draw_switchDown (Set[i].x, Set[i].y, Set[i].radius);
            }
        }
   }

void Draw_switchDown (int x, int y, int radius)
    {
    txSetColor(RGB(0, 100, 200), 2);
    txSetFillColor(TX_GREY);
    Title_Sort    (x - 4, y - 30, 10, 7, TX_WHITE,  "1");
    txCircle (x, y, radius);
    txSetColor(RGB(0, 100, 200));
    txSetFillColor(TX_BLACK);
    txRectangle(x - 5 , y, x + 5, y + 20);
    Title_Sort    (x - 4, y + 30, 10, 7, TX_WHITE,  "0");
    }

void Draw_switchUp (int x, int y, int radius)
    {
    txSetColor(RGB(0, 100, 200), 2);
    txSetFillColor(TX_GREY);
    Title_Sort    (x - 4, y - 30, 10, 7, TX_WHITE,  "1");
    txCircle (x, y, radius);
    txSetColor(RGB(0, 100, 200));
    txSetFillColor(TX_BLACK);
    txRectangle (x - 5, y, x + 5, y - 20);
    Title_Sort    (x - 4, y + 30, 10, 7, TX_WHITE,  "0");
    }

void Gradient()
    {
    for (int grad = 1; grad < 250; grad ++)
        {
        txSetColor     (RGB (0 + 0.3*grad, 0 + 0.3*grad, 30 + 0.3*grad));
        txSetFillColor (RGB (0 + 0.3*grad, 0 + 0.3*grad, 30 + 0.3*grad));

        POINT fon [4] = {{  0, 820 - 4*grad}, {  0, 830 - 4*grad},
                         {970, 830 - 4*grad}, {970, 820 - 4*grad}};
        txPolygon (fon, 4);
        }
    }


int ButtonCheckClickRound  (int x, int y, int radius, int mouse_x, int mouse_y)
    {
    if (fabs ((x - radius) - mouse_x) <= 2*radius)
        if (fabs ((y - radius) - mouse_y) <= 2*radius)
            if (GetAsyncKeyState (VK_LBUTTON))
                {
                return 1;
                };
    return 0;
    };


void Print_array (int array[])
    {
    for (int i = 0; i < 9; i ++)
        {
        printf ("%5d ", array[i]);
        }
    printf("\n");
   }



void SwitchCheck (struct Switch Set[], int array[])
    {

    for (int i = 0; i < 9; i ++)
        {

        if (ButtonCheckClickRound (Set[i].x, Set[i].y, Set[i].radius, txMouseX(), txMouseY()) == true)
            {
            array[i] = 1;
            txPlaySound ("metalsw3.WAV", SND_ASYNC);
            txClear();
            Gradient();
            Draw_Switch (Set1, first_number);
            Draw_Switch (Set2, second_number);
            Draw_Button (buttons);
            }
        }
    if (ButtonCheckClick (buttons[0].x, buttons[0].y, txMouseX(), txMouseY()) == true)
        {
        Clear_Array (first_number);
        Clear_Array (second_number);
        Clear_Array (lamp_set);
        txClear();
        Gradient();
        Draw_Switch (Set1, first_number);
        Draw_Switch (Set2, second_number);
        Draw_Button (buttons);
        }

    if (ButtonCheckClick (buttons[1].x, buttons[1].y, txMouseX(), txMouseY()) == true)
        {
        int a = decoder(first_number);
        int b = decoder(second_number);
        int sum = pluss(a, b);
        zacoder(lamp_set, sum);

        }

    if (ButtonCheckClick (buttons[2].x, buttons[2].y, txMouseX(), txMouseY()) == true)
        {
        txGetAsyncKeyState (VK_ESCAPE);
        }

    }



void Draw_Lamps  (struct Switch Lamps[], int array[], COLORREF from, COLORREF to, int time, int steps)
    {

    for (int i = 0; i < 9; i ++)
        {
        if (array[i]==1)
            {
            int r0 = txExtractColor (from, TX_RED),  r1 = txExtractColor (to, TX_RED),
            g0 = txExtractColor (from, TX_GREEN),    g1 = txExtractColor (to, TX_GREEN),
            b0 = txExtractColor (from, TX_BLUE),     b1 = txExtractColor (to, TX_BLUE);
            for (int k = 0; k <= steps; k++)
                {
                int r = r0 + (r1 - r0) * k/steps,
                g = g0 + (g1 - g0) * k/steps,
                b = b0 + (b1 - b0) * k/steps;
                txSetFillColor (RGB (r, g, b));

                txCircle (Lamps[i].x, Lamps[i].y, Lamps[i].radius);

                Sleep (time / steps);
                }

             }
        else
            {
            txSetFillColor (RGB(204, 204, 204));
            txCircle (Lamps[i].x, Lamps[i].y, Lamps[i].radius);
            }
     }
    }


void Draw_Button (struct ButtonType buttons[])
    {

    for (int i = 0; i < 3; i ++)
        {
        txSetColor      (buttons[i].colortext, 3);
        txSetFillColor  (RGB (0, 50, 121));
        txRectangle (buttons[i].x, buttons[i].y, buttons[i].x + 100, buttons[i].y + 40);
        Title_Sort  (buttons[i].x + 5, buttons[i].y + 8, 16, 10, buttons[i].colortext, buttons[i].name);
        }
   }


void Title_Sort (int x, int y, int size, int high, COLORREF color_title, char name[])
    {
    txSetColor    (color_title);
    txSelectFont  ("Arial", size, high);
    char str [20] = "";
    sprintf (str, "%s", name);
    txTextOut (x, y, str);
    }

int ButtonCheckClick (int x, int y, int mouse_x, int mouse_y)
    {
    if (fabs (x - mouse_x) <= 100)
        if (fabs (y - mouse_y) <= 40)
            if (GetAsyncKeyState (VK_LBUTTON))
                {
                return 1;
                };
    return 0;
    };

//Functions

int decoder(int  array[])
{
    int ch = 0;
    int k = 1;
    for (int i = 8; i >= 1; i--)
    {
        if (array[i] == 1) ch += 1 * k;
        k *= 2;
    }
    if (array[0] == 1) ch *= (-1);
    return ch;
}

int pluss(int x, int y)
{
    int s = 0;
    s = x + y;
    return s;
}


void zacoder(int itog[], int sum)
{
    int mas[9];

    if (sum < 0)
    {
        mas[8] = 1; sum *= -1;
    }
    else mas[8] = 0;

    for (int i = 0; i < 8; i++)
    {
        mas[i] = sum % 2;
        sum /= 2;
    }

    for (int i = 0; i < 9; i++)
    {
        itog[i] = mas[9 - 1 - i];
    }
}

