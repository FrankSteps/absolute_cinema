/*
    Teste com C++ e biblioteca SFML
    Desenvolvido por: Francisco Passos
    Desenvolvido em: 31/07/2025

    Com a variável alpha, é possível criar um efeito de transparência na imagem 
    Mas ao implementár-mos a função "contador" (descrito formalmente no código), cria-se o efeito de "vinheita" na imagem
*/

//Variaveis usadas no projeto
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

//declaração das namespaces utilizadas por algumas das bibliotecas
using namespace std;
using namespace sf;

//declaração da variável alpha
int alpha = 0; 

//função de delay - com o uso semelhante ao c++ do arduino
void delay(int valor){
    this_thread::sleep_for(chrono::milliseconds(valor)); 
}

//função responsável por alterar o valor de alpha unitariamente de 0 para 255
void contador(){
    delay(3000);
    for(int i = 0; i <= 255; i++){
        alpha = i; 
        delay(10); //chamando a função delay();
    }
}

int main() {
    //algumas configurações de exibição da janela
    RenderWindow window(VideoMode(1024, 868), "Absolute cinema");

    //Responsável por "puxar" a imagem para o código
    Texture texture;
    if (!texture.loadFromFile("images_a/cinema.jpeg")) {
        return -1; //fecha o programa automaticamente caso a imagem não seja encontrada ou esteja corrompida
    }
    Sprite sprite(texture);

    //configurações de interação com a janela
    thread fadeThread(contador); 
    while (window.isOpen()) {
        sprite.setColor(Color(255, 255, 255, alpha));

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //ultimas configurações da janela
        window.clear();
        window.draw(sprite); //mostra a imagem - sempre atualizando permitindo a visualização do efeito
        window.display();
    }
    fadeThread.join(); 
    return 0;
}
