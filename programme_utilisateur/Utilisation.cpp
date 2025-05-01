/**
 * \file Utilisation.cpp
 * \brief Programme principal utilisant la classe Client pour afficher les différents comptes.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 avril 2025
 */
#include <cstdlib>
#include "Compte.h"
#include "Epargne.h"
#include "Cheque.h"
#include "Client.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace bancaire;
using namespace util;

util::Date obtenirDateNaissanceValide(const string &dateNaissance);
Client saisirClient();
Cheque saisirInformationsCompteCheque(const util::Date &dateOuverture);
Epargne saisirInformationsCompteEpargne(const util::Date &dateOuverture);
util::Date saisieDateActuelle();

int main()
{
  cout << "-----------------------------------------------" << endl;
  cout << "Bienvenue a l'outil de gestion de comptes" << endl;
  cout << "-----------------------------------------------" << endl;

  util::Date dateOuverture = saisieDateActuelle();
  Client client = saisirClient();
  Cheque compteCheque = saisirInformationsCompteCheque(dateOuverture);
  Epargne compteEpargne = saisirInformationsCompteEpargne(dateOuverture);
  // Affichage des informations du client
  cout << endl;
  cout << "Relevé de compte";
  cout << "\n----------------------------" << endl;
  cout << client.reqClientFormate();
  cout << compteCheque.reqCompteFormate();
  cout << compteEpargne.reqCompteFormate();

  return 0;
}
/**
 * 
 * @brief Obtention d'une date de naissance valide du client
 * @param[in] dateNaissance
 * @return La date de naissance valide
 */
util::Date obtenirDateNaissanceValide(const string &dateNaissance)
{
  cout << "Date de naissance" << endl;
  int jourNaissance, moisNaissance, anneeNaissance;
  bool validationDate;
  do
  {
    cout << "Le jour [1...31]: ";
    cin >> jourNaissance;

    cout << "Le mois [1...12]: ";
    cin >> moisNaissance;

    cout << "L'année : ";
    cin >> anneeNaissance;

    if (jourNaissance < 1 || jourNaissance > 31 || moisNaissance < 1 || moisNaissance > 12 || anneeNaissance < 1970 || anneeNaissance > 2037)
    {
      cout << "date invalide, recommencez" << endl;
      validationDate = false;
    }
    else
    {
      validationDate = true;
    }
  } while (!validationDate);

  return util::Date(jourNaissance, moisNaissance, anneeNaissance);
}

/**
 * 
 * @brief Saisie et validation des informations d'un nouveau client
 * @return Les informations du clients saisies par l'utilisateur apres validation
 */
Client saisirClient()
{
  cout << "Saisir les informations sur le nouveau Client" << endl;
  int noFolio;
  string nom, prenom, telephone;

  do
  {
    cout << "Folio : ";
    cin >> noFolio;
    cin.ignore();

    if (noFolio <= 1000 || noFolio >= 10000)
    {
      cout << "numéro incorrect, doit être dans l’intervalle [1000, 10000[, recommencez" << endl;
    }
  } while (noFolio <= 1000 || noFolio >= 10000);

  do
  {
    cout << "Nom : ";
    getline(cin, nom);

    if (!Client::validerFormatNom(nom))
    {
      cout << "nom invalide, recommencez" << endl;
    }
  } while (!Client::validerFormatNom(nom));

  do
  {
    cout << "Prénom : ";
    getline(cin, prenom);

    if (!Client::validerFormatNom(prenom))
    {
      cout << "prenom invalide, recommencez" << endl;
    }
  } while (!Client::validerFormatNom(prenom));

  util::Date dateNaissance = obtenirDateNaissanceValide("Date de naissance");

  cin.ignore ();
  do
  {
    cout << "Téléphone : ";
    getline(cin, telephone);

    if (telephone.empty())
    {
      cout << "téléphone invalide, recommencez" << endl;
    }

  } while (telephone.empty());

  return Client(noFolio, nom, prenom, telephone, dateNaissance);
}

/**
 * 
 * @brief Saisie et validation des informations d'un nouveau compte cheque
 * @return Les informations du compte cheque saisies par l'utilisateur apres validation
 */
Cheque saisirInformationsCompteCheque(const util::Date &dateOuverture)
{
  cout << "Saisir les informations sur le nouveau compte Cheque" << endl;
  int numeroCompteCheque, nombreTransactions;
  double tauxInteretCheque, soldeCheque, tauxInteretMinimum;
  string descriptionCheque;

  do
  {
    cout << "numéro de compte? ";
    cin >> numeroCompteCheque;
    if (numeroCompteCheque <= 0)
    {
      cout << "numéro de compte invalide, recommencez" << endl;
    }
  } while (numeroCompteCheque <= 0);
  cin.ignore ();
  
  do
  {
    cout << "Description: ";
    getline(cin, descriptionCheque);
    if (descriptionCheque.empty())
    {
      cout << "description invalide, recommencez" << endl;
    }
  } while (descriptionCheque.empty());

  do
  {
    cout << "Taux d'Interet : ";
    cin >> tauxInteretCheque;
    if ((tauxInteretCheque / 100) <= 0)
    {
      cout << "taux interet invalide, recommencez" << endl;
    }
  } while ((tauxInteretCheque / 100) <= 0);

  do
  {
    cout << "Solde : ";
    cin >> soldeCheque;
    if (soldeCheque < 0)
    {
      cout << "solde invalide, recommencez" << endl;
    }
  } while (soldeCheque < 0);

  do
  {
    cout << "Nombre de transactions : ";
    cin >> nombreTransactions;
    if (nombreTransactions <= 0 || nombreTransactions > 40)
    {
      cout << "nombre de transactions invalide, recommencez" << endl;
    }
  } while (nombreTransactions <= 0 || nombreTransactions > 40);

  do
  {
    cout << "Taux d'intérêt minimum : ";
    cin >> tauxInteretMinimum;
    if ((tauxInteretMinimum / 100) < 0.001 || (tauxInteretMinimum / 100) >= (tauxInteretCheque / 100))
    {
      cout << "taux d'intérêt minimum invalide, recommencez" << endl;
    }
    if((tauxInteretMinimum / 100) >= tauxInteretCheque){
        cout << "taux d'intérêt minimum invalide, recommencez" << endl;
      }
  } while ((tauxInteretMinimum / 100) < 0.001 || (tauxInteretMinimum / 100) >= (tauxInteretCheque / 100));

  return Cheque(numeroCompteCheque, (tauxInteretCheque / 100), soldeCheque, dateOuverture, descriptionCheque, nombreTransactions, (tauxInteretMinimum / 100));
}

/**
 * 
 * @brief Saisie et validation des informations d'un nouveau compte epargne
 * @return Les informations du compte epargne saisies par l'utilisateur apres validation
 */
Epargne saisirInformationsCompteEpargne(const util::Date &dateOuverture)
{
  cout << "Saisir les informations sur le nouveau compte Epargne" << endl;
  int numeroCompteEpargne;
  double tauxInteretEpargne, soldeEpargne;
  string descriptionEpargne;

  do
  {
    cout << "numéro de compte? ";
    cin >> numeroCompteEpargne;
    if (numeroCompteEpargne <= 0)
    {
      cout << "numéro de compte invalide, recommencez" << endl;
    }
  } while (numeroCompteEpargne <= 0);
  cin.ignore ();
  do
  {
    cout << "Description: ";
    getline(cin, descriptionEpargne);
    if (descriptionEpargne.empty())
    {
      cout << "description invalide, recommencez" << endl;
    }
  } while (descriptionEpargne.empty());

  do
  {
    cout << "Taux d'Interet : ";
    cin >> tauxInteretEpargne;
    if ((tauxInteretEpargne / 100) < 0.001 || (tauxInteretEpargne / 100) > 0.035)
    {
      cout << "taux interet invalide, recommencez" << endl;
    }
  } while ((tauxInteretEpargne / 100) < 0.001 || (tauxInteretEpargne / 100) > 0.035);

  do
  {
    cout << "Solde : ";
    cin >> soldeEpargne;
    if (soldeEpargne < 0)
    {
      cout << "solde invalide, recommencez" << endl;
    }
  } while (soldeEpargne < 0);

  return Epargne(numeroCompteEpargne, (tauxInteretEpargne / 100), soldeEpargne, dateOuverture, descriptionEpargne);
}

/**
 * 
 * @brief Obtention de la date actuelle
 * @return La date actuelle
 */
util::Date saisieDateActuelle()
{
  time_t tempsActuel = std::time(nullptr);
  tm tempsLocal = *localtime(&tempsActuel);
  return util::Date(tempsLocal.tm_mday, tempsLocal.tm_mon + 1, tempsLocal.tm_year + 1900);
}