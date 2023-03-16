# LineFollower

***Introducere***

Mașină cu 3 roți, una fiind mobilă, și 2 motoare care vor urmări path-ul unei linii negre. (curbele si direcția) Scopul acestui proiect este de a realiza o comunicarea eficientă între plăcuța Arduino și cele 2 motoare pe baza inputului de la senzor.

***Descriere generală***

Utilizatorul va avea posibilitatea de a porni printr-un switch mașinuța.
Mișcarea mașinii va fi controlată de către driver-ul de motor pe baza informației provenite din partea un bări de senzori infraroșu reflectivi. Cele 2 motoare conectate la driver vor fi primi semnale potrivite pentru a acționa mașina în direcția dorită.

***Software Design***

Acest proiect este împărțit în 3 părți:

- Citirea și calibrarea celor 8 senzori infraroșu.
- Algoritmul PID pentru calcularea vitezei și interpretarea datelor de la senzori.
- Setarea vitezei motoarelor.

Am folosit biblioteca QTRSensors.h pentru a citi senzorii și am setat manual motoarele cu digitalWrite.

În timpul dezvoltării software, am abordat multe modalități de calcul al vitezelor pentru cele 2 motoare. De la cea mai complicată abordare care mergea doar pe o linie dreaptă, am atins și un comportament funcțional doar pentru curbe. Între timp am descoperit cu ajutorul laborantului că ar trebui să folosesc algoritmul PID.
