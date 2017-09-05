# Intro

Segue uma lista de imagens que podem servir de refer�ncia para avaliar se o shader Blinn-Phong est� funcionando ou n�o.

# Configura��o de Imagem

Imagem:

+ largura: 1200
+ altura: 600
+ samples per pixel: 1
+ recursion depth: 1

# Configura��o de C�mera

Camera:

+ origem: (0,0,0)
+ lower left corner: (-2, -1, -1)
+ vertical: (0,2,0)
+ horizontal: (4,0,0)

# Configura��o de Cena

Atores:

+ Esfera #1: o ch�o:
    - centro: (0,-100.5,-1)
    - raio: 100
    - material:
        * ambiente: (0.1,0.1,0.1)
        * difuso: (0.4,0.4,0.4)
        * specular: (1,1,1)
        * expoente especular: 5

+ Esfera #2: esfera central:
    - centro: (0,0,-1)
    - raio: 0.4
    - material:
        * ambiente: (0.1,0.1,0.1)
        * difuso: (0.0,0.3,0.8)
        * specular: (0.9,0.9,0/9)
        * expoente especular: 64 (variando para cada imagem)

A cena foi gerada com apenas 1 luz direcional e 1 luz ambiente.
As luzes:

- luz direcional:
    + intensidade (1,1,1)
    + dire��o (20,10,5)
- ambiente:
    + intensidade (0.4,0.4,0.4)

# As imagens
+ img_0: Nenhuma luz ativada no ambiente.
+ img_1: Apenas a luz ambiente ativada.
+ img_2: Apenas o componente difuso ativado (ambiente desligado).
+ img_3: Apenas o componente especular ativado (ambiente desligado).
+ img_4: Especular e difuso ativos, coeficiente especular = 64 (ambiente desligado).
+ img_5: Especular e difuso ativos, coeficiente especular = 32 (ambiente desligado).
+ img_6: Especular e difuso ativos, coeficiente especular = 16 (ambiente desligado).
+ img_7: Especular e difuso ativos, coeficiente especular = 4 (ambiente desligado).
+ img_8: Especular e difuso ativos, coeficiente especular = 64 (ambiente LIGADO).
