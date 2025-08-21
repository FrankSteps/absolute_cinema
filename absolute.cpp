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

//declaração da variável alpha
int alpha = 0; 

//função de delay - com o uso semelhante ao c++ do arduino
void delay(int valor){
    std::this_thread::sleep_for(std::chrono::milliseconds(valor)); 
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
    sf::RenderWindow window(sf::VideoMode(1024, 868), "Absolute cinema");

    //Responsável por "puxar" a imagem para o código
    sf::Texture texture;
    if (!texture.loadFromFile("images_a/cinema.jpeg")) {
        return -1; //fecha o programa automaticamente caso a imagem não seja encontrada ou esteja corrompida
    }
    sf::Sprite sprite(texture);

    //configurações de interação com a janela
    std::thread fadeThread(contador); 
    while (window.isOpen()) {
        sprite.setColor(sf::Color(255, 255, 255, alpha));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
