#include<iostream>
#include<queue>
#include<vector>
#include<cmath>
#include <SFML/Graphics.hpp>
using namespace std;


//----------------------------------------------Estructura Arbol----------------------
struct ArNode
{
    int x,y;
    char value;
    ArNode* nodes[2];
    sf::CircleShape shape;
    sf::Text text;
    sf::Font font;

    //Modulo, anchura
    sf::RectangleShape LineLeft;
    //angulo respecto a -x
     sf::RectangleShape LineRight;
   

    
    ArNode(char _v): shape(30.f), LineLeft(sf::Vector2f(70.f, 5.f)), LineRight(sf::Vector2f(70.f, 5.f))
    {
        //x = 200; y = 50
        this->x = 0; this->y = 0;
        value = _v; nodes[0] = nodes[1] = 0;

       
        shape.setFillColor(sf::Color::Green);
        

        font.loadFromFile("Bubble Mint.otf");

        
        text.setString(_v);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Blue);
       
      
        
    }
    void Sets()
    {
        text.setFont(font); 
        text.setPosition(x+18,y-5);

        shape.setPosition(this->x,this->y);
        
        
        
        
    }   
    void SetsLines()
    {
        

        
        if(nodes[0])
        {
            LineLeft.setPosition(x+33,y+58);
           // cout<<180/M_PI*ata    n(x-nodes[0]->x )/(nodes[0]->y - y)<<endl;
            LineLeft.rotate(180/M_PI*atan(( x-nodes[0]->x )/(nodes[0]->y - y) )+90);
            
            LineLeft.setSize(sf::Vector2f(sqrt(pow(x- nodes[0]->x, 2)+ pow(nodes[0]->y-y,2)), 5.f));
        }
        if(nodes[1])
        {
            float c = sqrt(pow(nodes[1]->x - x, 2)+ pow(nodes[1]->y-y,2));
            float b = nodes[1]->x -x;
            //cout<<90-180/M_PI*(atan((nodes[1]->x - x)/(nodes[1]->y - y)))<<"  ->  "<<(nodes[1]->x - x)<<" - "<<(nodes[1]->y - y)<<endl;
            LineRight.setPosition(x+33,y+58);
            //                                atan(( x-nodes[0]->x )/(nodes[0]->y - y) )+90
            float rotacion = 90-180/M_PI*(asin(b/c ));
            //cout<<nodes[1]->x<<" - " <<x<<endl;
            cout<<"-> "<<rotacion<<endl;
            
            LineRight.rotate(rotacion);
            LineRight.setSize(sf::Vector2f(c, 5.f));
            
        }
    }
    void DrawNode(sf::RenderWindow &a)
    {       

        

        
        
        if(nodes[0])
        {
            
            a.draw((LineLeft));
            
        }
        if(nodes[1])
        {
            
            a.draw((LineRight));
        }
        a.draw((shape));
        a.draw((text));
    }
};

struct ArTree
{
    ArNode* root;
    sf::RenderWindow window;
    ArTree():window(sf::VideoMode(1500, 900), "Arbol Aritmetico!")
    {
        window.setFramerateLimit(60);
        root = 0;
    }
    void InOrder(ArNode* n, vector<ArNode*> &a)
    {
        if (!n) return;

        InOrder(n->nodes[0],a);
        a.push_back(n);
        InOrder(n->nodes[1], a);
    }
    void PreOrder(ArNode* n,vector<ArNode*> &a)
    {
        if (!n) return;
        a.push_back(n);
        PreOrder(n->nodes[0],a);
        PreOrder(n->nodes[1], a);
    }
    void PostOrder(ArNode* n)
    {
        if (!n) return;

        PostOrder(n->nodes[0]);
        PostOrder(n->nodes[1]);
        cout << n->value << "-";
    }
    void Profundidad(ArNode*n)
    {
        std::queue<ArNode*> q;
        q.push(n);
        

        while(q.size()>0)
        {
            if(q.front()->nodes[0])q.push(q.front()->nodes[0]);
            if(q.front()->nodes[1])q.push(q.front()->nodes[1]);
            
            q.front()->DrawNode(window);
            q.pop();
        }
    }
    void Prof(ArNode*n)
    {
        std::queue<ArNode*> q;
        q.push(n);
        

        while(q.size()>0)
        {
            if(q.front()->nodes[0])q.push(q.front()->nodes[0]);
            if(q.front()->nodes[1])q.push(q.front()->nodes[1]);
            cout<<q.front()->value;
            q.pop();
        }
    }
    void Print()
    {   
        Profundidad(root) ;
        
        cout << endl;
    }   
    void LogicNodePosition()
    {
        vector<ArNode*> inorder;
        vector<ArNode*> preorder;
        
        InOrder(root,inorder);
        PreOrder(root,preorder);

        
        
        for (int i = 0; i  < inorder.size(); i++)
        {
            int j = 0;
            for(; ref(inorder[i]) != ref(preorder[j])  && j < preorder.size(); j++);
            
            inorder[i]->x = (i+1)*70;
            
            inorder[i]->y = (j+1)*70;
            
            inorder[i]->Sets();
        }
        for (int i = 0; i  < inorder.size(); i++)
        {
            preorder[i]->SetsLines();
        }

    }
    void Draw()
    {

        LogicNodePosition();

        
        while (window.isOpen())
        {
            
        
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            Profundidad(root);
            window.display();
            
        }
    }
    int GetHeight(ArNode *node) 
    {
        if (node == NULL) return 0;
        return 1 + max(GetHeight(node->nodes[0]), GetHeight(node->nodes[1]));
    }
};

//---------------------------------------------Rellenar Arbol-----------------------------
int SearchOp(string a)
{
    int tamanho = a.size();
    int parentesis = 0;
    int i = 0;
    bool sumaresta = false;
    int retornar = -1;
    for(; i <tamanho; i++)
    {
        if(a[i] == '(') parentesis++;
        else if(a[i] == ')') parentesis--;
        if(parentesis == 0 && (a[i] == 43 || a[i] == 45) )
        {
            retornar = i;
            sumaresta = true;
        }
        if(parentesis == 0 && sumaresta == false && (a[i] == 42 || a[i] == 47)) 
        {
            retornar = i;
            
        }
        //cout<<a[i]<<endl;
    }
    return retornar;
}


string AsingLeft(string a, int p)
{
    string returner;
    int tamanho = p;
    int i = 0;
    if(a[0] == '(' && a[tamanho-1] == ')'){i++;tamanho--;}
    for(;i<tamanho;i++)
    {
        returner.push_back(a[i]);
    }
    
    return returner;
}
string AsingRight(string a, int p)
{
    string returner;
    int tamanho = a.size();
    int i = p+1;
    if(a[p+1] == '(' && a[tamanho-1] == ')'){i++;tamanho--;}
    for(;i<tamanho;i++)
    {
        returner.push_back(a[i]);
    }
    
    return returner;
}
//2+3
string a1(string a,ArNode *&root)
{
    int tamanho = a.size();
    if(tamanho == 1)
    {
        root = new ArNode(a[0]);
        return a;
    }
    int i = SearchOp(a);
    string left = AsingLeft(a,i);
    string right = AsingRight(a,i);

    root = new ArNode(a[i]);
    a1(left,root->nodes[0]);
    a1(right,root->nodes[1]);
    return "xd"; 
}

//--------------------------------------SFML------------------------------------------














/*sfml
#!/bin/bash

clear
g++ -c $1.cpp
g++ -c $1.cpp -I/usr/include/SFML/include
g++ -Wall $1.o -o sfml-app -L/usr/include/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app

*/
