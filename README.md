# Gestion de Comptes Bancaires en C++ 💰

Ce projet est une application console en C++ simulant la gestion de comptes bancaires pour des clients, réalisée dans le cadre du cours **Programmation avancée en C++ (GIF-1003)**.

## 🧰 Fonctionnalités principales

- Hiérarchie de classes : `Compte` (classe de base), `Epargne`, `Cheque`
- Gestion de clients avec plusieurs comptes via `std::vector<std::unique_ptr<Compte>>`
- Calcul polymorphe des intérêts
- Relevés de comptes formatés
- Implémentation de la **théorie du contrat** (préconditions, invariants, postconditions)
- Tests unitaires pour chaque classe (`CompteTesteur.cpp`, etc.)
- Gestion mémoire moderne avec `std::unique_ptr`
- Documentation complète générée avec **Doxygen**

# Auteur
Aubry Nobel Niyonkuru
Étudiant en Baccalauréat en informatique à l’Université Laval
📧 nobelaubry5@gmail.com


