/**
 * \file Client.cpp
 * \brief Implémentation de la classe Client.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#include "Client.h"
#include "Date.h"
#include "Compte.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ContratException.h"
#include <vector>
#include <memory>

/**
 * \brief Constructeur de la classe Client
 * \param[in] p_noFolio Le numéro de folio du client
 * \param[in] p_nom Le nom du client
 * \param[in] p_prenom Le prénom du client
 * \param[in] p_telephone Le numéro de téléphone du client
 * \pre p_noFolio doit être supérieur a 1000 et inférieur a 10000
 * \pre p_nom et p_prenom doivent respecter un format valide
 * \pre p_telephone ne doit pas être vide
 * \pre p_dateNaissance doit avoir une année supérieur a 1970 et inferieur a 2037
 * \post m_noFolio prends la valeur de p_noFolio
 * \post m_nom prends la valeur de p_nom
 * \post m_prenom prends la valeur de p_prenom
 * \post m_telephone prends la valeur de p_telephone
 * \post m_dateNaissance prends la valeur de p_dateNaissance
 * 
 */
Client::Client (int p_noFolio, const std::string &p_nom, const std::string &p_prenom,
                const std::string &p_telephone, const util::Date &p_dateNaissance) : m_noFolio (p_noFolio), m_nom (p_nom), m_prenom (p_prenom), m_telephone (p_telephone), m_dateNaissance (p_dateNaissance.reqJour (), p_dateNaissance.reqMois (), p_dateNaissance.reqAnnee ())
{
  PRECONDITION (p_noFolio >= 1000 && p_noFolio <= 10000);
  PRECONDITION (validerFormatNom (p_nom));
  PRECONDITION (validerFormatNom (p_prenom));
  PRECONDITION (!p_telephone.empty ());
  PRECONDITION (p_dateNaissance.reqAnnee () >= 1970 && p_dateNaissance.reqAnnee () <= 2037);

  POSTCONDITION (m_noFolio == p_noFolio);
  POSTCONDITION (m_nom == p_nom);
  POSTCONDITION (m_prenom == p_prenom);
  POSTCONDITION (m_telephone == p_telephone);
  POSTCONDITION (m_dateNaissance == p_dateNaissance);
  INVARIANTS ();
}

/**
 * \brief Destructeur virtuel de Client
 */
Client::~Client () { }

/**
 * \brief Constructeur copie de la classe Client
 */
Client::Client (const Client &p_client) : m_noFolio (p_client.m_noFolio), m_nom (p_client.m_nom), m_prenom (p_client.m_prenom), m_telephone (p_client.m_telephone), m_dateNaissance (p_client.m_dateNaissance)
{
  for (const auto &compte : p_client.m_comptes)
    {
      m_comptes.push_back (compte->clone ());
    }
}

/**
 * \brief Opérateur d'assignation de la classe Client.
 */
Client &Client::operator= (const Client &p_client)
{
  if (this == &p_client)
    {
      return *this;
    }
  m_comptes.clear ();

  m_noFolio = p_client.m_noFolio;
  m_nom = p_client.m_nom;
  m_prenom = p_client.m_prenom;
  m_telephone = p_client.m_telephone;
  m_dateNaissance = p_client.m_dateNaissance;

  for (const auto &compte : p_client.m_comptes)
    {
      m_comptes.push_back (compte->clone ());
    }
  return *this;
}

/**
 * \brief Méthode accesseur pour obtenir la date d'ouverture du compte.
 * \return La date d'ouverture du compte.
 */
int
Client::reqNoFolio () const
{
  return m_noFolio;
}

/**
 * \brief Méthode accesseur pour obtenir le nom du client.
 * \return Le nom du client.
 */
std::string
Client::reqNom () const
{
  return m_nom;
}

/**
 * \brief Méthode accesseur pour obtenir le prenom du client.
 * \return Le prenom du client.
 */
std::string
Client::reqPrenom () const
{
  return m_prenom;
}

/**
 * \brief Méthode accesseur pour obtenir le numéro de téléphone du client.
 * \return Le numéro de téléphone du client.
 */
std::string
Client::reqTelephone () const
{
  return m_telephone;
}

/**
 * \brief Méthode accesseur pour obtenir la date de naissance du client.
 * \return La date du naissance du client.
 */
const util::Date &
Client::reqDateNaissance () const
{
  return m_dateNaissance;
}

/**
 * \brief Méthode mutateur pour modifier le nom du client
 * \param[in] p_nom Le nouveau nom du client
 * \pre p_nom doit respecter un format valide
 * \post m_nom prend la valeur de p_nom
 */
void
Client::asgNom (const std::string &p_nom)
{
  PRECONDITION (validerFormatNom (p_nom));
  m_nom = p_nom;
  POSTCONDITION (m_nom == p_nom);
  INVARIANTS ();
}

/**
 * \brief Méthode mutateur pour modifier le prénom du client
 * \param[in] p_prenom Le nouveau prénom du client
 * \pre p_prenom doit respecter un format valide
 * \post m_prenom prend la valeur de p_prenom
 */
void
Client::asgPrenom (const std::string &p_prenom)
{
  PRECONDITION (validerFormatNom (p_prenom));
  m_prenom = p_prenom;
  POSTCONDITION (m_prenom == p_prenom);
  INVARIANTS ();
}

/**
 * \brief Méthode mutateur pour modifier le numéro de téléphone du client
 * \param[in] p_telephone Le nouveau numéro de téléphone du client
 * \pre p_telephone ne doit pas être vide
 * \post m_telephone prend la valeur de p_telephone
 */
void
Client::asgTelephone (const std::string &p_telephone)
{
  PRECONDITION (!p_telephone.empty ());
  m_telephone = p_telephone;
  POSTCONDITION (m_telephone == p_telephone);
  INVARIANTS ();
}

/**
 * \brief Valide le format d'un nom (nom ou prénom)
 * \param[in] p_nom a valider.
 * \return true si le format est valide, false sinon
 */
bool
Client::validerFormatNom (const std::string &p_nom)
{

  // Verifier si la chaine est vide
  if (p_nom.length () == 0)
    {
      return false;
    }

  // Initialisation de la variable contenant les caracteres accentues permis
  const std::string listeAccents = "àâäéèêëîïôöùûüç";

  bool finEspaceTiret = false;

  // Boucle qui itere chaque caractere du nom
  for (size_t i = 0; i < p_nom.length (); ++i)
    {

      // Variable recuperant chaque caractere
      char caractere = p_nom[i];

      // Verifier si c'est une lettre majuscule, minuscule, un caractere accentue, un espace ou tiret
      // npos -Retourne la position du caractere trouve par find()
      if (!((caractere >= 'a' && caractere <= 'z') ||
            (caractere >= 'A' && caractere <= 'Z') ||
            listeAccents.find (caractere) != std::string::npos || caractere == ' ' || caractere == '-'))
        {
          return false;
        }

      // Vérifier que les espaces et tirets sont uniquement entre les mots
      if (caractere == ' ' || caractere == '-')
        {
          // Verifier si il y a des espaces ou tirets au début, à la fin, ou consécutifs
          if (i == 0 || i == p_nom.length () - 1 || finEspaceTiret)
            {
              return false;
            }
          finEspaceTiret = true;
        }
      else
        {
          finEspaceTiret = false;
        }
    }
  return true;
}

/**
 * \brief Ajouter le compte au client
 * \param[in] p_nouveauCompte Le compte a ajouter.
 * */
void
Client::ajouterCompte (const bancaire::Compte &p_nouveauCompte)
{
  m_comptes.push_back (p_nouveauCompte.clone ());
}

/**
 * \brief Affiche les informations du Client sous forme d'une chaîne de caractère formatee
 * \return les information du client
 */
std::string
Client::reqClientFormate () const
{
  std::ostringstream oss;
  oss << "Client no de folio : " << m_noFolio << std::endl;
  oss << m_prenom << " " << m_nom << std::endl;
  oss << "Date de naissance: " << m_dateNaissance << std::endl;
  oss << m_telephone << std::endl;
  return oss.str ();
}

std::string
Client::reqReleves () const
{
  std::ostringstream oss;
  oss << reqClientFormate () << std::endl;

  oss << "Comptes:\n";
  for (const auto &compte : m_comptes)
    {
      oss << compte->reqCompteFormate () << std::endl;
    }
  return oss.str ();
}

void
Client::verifieInvariant () const { }
