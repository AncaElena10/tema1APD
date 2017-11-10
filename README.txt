APD - TEMA1 - CONWAY'S GAME OF LIFE
Moisa Anca-Elena 331 CA

Prezentare generala
-------------------

- am citit din fisier datele necesare (numarul de linii, numarul de coloane 
si matricea formata din X si .); de asemenea din linia de comanda am extras 
numarul de iteratii, fisierul de input si cel de output;
- am alocat dinamic cele doua spatii de lucru (matricea originala si cea 
auxiliara in care pastrez valorile de la pasul anterior);

La fiecare pas:
-------------------------------------------------------------------------------
-> am creat o noua copie pentru matricea de la pasul anterior
-> am bordat matricea auxiliara in interiorului buclei de iteratii pentru a nu 
omite noile elemente aparute (modalitate de bordare: linia superioara va fi 
bordata cu cea inferioara, coloana din dreapta va fi bordata cu cea din stanga,
linia inferioara bordata cu cea superioara, si coloana din stanga bordata cu 
cea din dreapta; pentru colturi - cel din stanga sus bordat cu cel din dreapta 
jos, cel din dreapta sus cu cel din stanga jos, coltul din dreapta jos bordat 
cu cel din stanga sus, iar cel din stanga jos cu cel din dreapta sus);
-> am calculat (pentru a tine cont de reguli) suma pentru o celula (astfel, X 
in ASCII va fi 88, iar . 46);
- daca o celula are 3 vecini, inseamna ca 3*88 va fi suma pentru ei, si 5*46 
va fi suma pentru celulele goale (am calculat in acelasi mod si pentru restul 
cazurilor);
-------------------------------------------------------------------------------

- in final am afisat in fisierul de output matricea de la ultima generatie si am 
eliberat matricele utilizate.

Pentru imbunatatire, am paralelizat:
- alocarea matricei
- bordarea matricei
- partea din cod care se ocupa efectiv cu calculul vecinilor
- crearea unei copii pentru matricea de la pasul anterior
