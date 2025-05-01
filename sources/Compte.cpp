/**
 * \file Compte.cpp
 * \brief Implémentation de la classe de base abstraite Compte.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#include "Compte.h"
#include "Date.h"
#include <iostream>
#include <sstream>
#include "ContratException.h"

using namespace bancaire;
/**
 * \brief Constructeur de la classe Compte.
 * \param p_noCompte Le numéro de compte.
 * \param p_tauxInteret Le taux d'intérêt du compte.
 * \param p_solde Le solde initial du compte.
 * \param p_description La description du compte.
 * \param p_dateOuverture La date d'ouverture du compte.
 * \pre p_noCompte doit etre positif
 * \pre p_description ne doit pas etre vide
 * \post m_noCompte prends la valeur de p_noCompte
 * \post m_tauxInteret prends la valeur de p_tauxInteret
 * \post m_solde prends la valeur de p_solde
 * \post m_description prends la valeur de p_description
 * \post m_dateOuverture prends la valeur de p_dateOuverture
 */
Compte::Compte(int p_noCompte, double p_tauxInteret, double p_solde, const std::string &p_description, const util::Date &p_dateOuverture) : m_noCompte(p_noCompte), m_tauxInteret(p_tauxInteret), m_solde(p_solde), m_description(p_description), m_dateOuverture(p_dateOuverture.reqJour(), p_dateOuverture.reqMois(), p_dateOuverture.reqAnnee())
{

  PRECONDITION(p_noCompte > 0);
  PRECONDITION(!p_description.empty());

  POSTCONDITION(m_noCompte == p_noCompte);
  POSTCONDITION(m_tauxInteret == p_tauxInteret);
  POSTCONDITION(m_solde == p_solde);
  POSTCONDITION(m_description == p_description);
  POSTCONDITION(m_dateOuverture == p_dateOuverture);
  INVARIANTS();
}

/**
 * \brief Destructeur virtuel de la classe Compte.
 */
Compte::~Compte() {}

/**
 * \brief Méthode accesseur pour obtenir le numéro de compte.
 * \return Le numéro de compte.
 */
int Compte::reqNoCompte() const
{
  return m_noCompte;
}

/**
 * \brief Méthode accesseur pour obtenir le taux d'intérêt.
 * \return Le taux d'intérêt.
 */
double
Compte::reqTauxInteret() const
{
  return m_tauxInteret;
}

/**
 * \brief Méthode accesseur pour obtenir le solde du compte.
 * \return Le solde du compte.
 */
double
Compte::reqSolde() const
{
  return m_solde;
}

/**
 * \brief Méthode accesseur pour obtenir la description du compte.
 * \return La description du compte.
 */
std::string
Compte::reqDescription() const
{
  return m_description;
}

/**
 * \brief Méthode accesseur pour obtenir la date d'ouverture du compte.
 * \return La date d'ouverture du compte.
 */

const util::Date &Compte::reqDateOuverture() const
{
  return m_dateOuverture;
}

/**
 * \brief Méthode mutateur pour modifier le taux d'intérêt.
 * \post m_tauxInteret == p_tauxInteret
 */
void Compte::asgTauxInteret(double p_tauxInteret)
{
  m_tauxInteret = p_tauxInteret;
  POSTCONDITION(m_tauxInteret == p_tauxInteret);
  INVARIANTS();
}

/**
 * \brief Méthode mutateur pour modifier le solde du compte.
 * \post m_solde == p_solde
 */
void Compte::asgSolde(double p_solde)
{
  m_solde = p_solde;
  POSTCONDITION(m_solde == p_solde);
  INVARIANTS();
}

/**
 * \brief Méthode mutateur pour modifier la description du compte.
 * \post m_description == p_description
 */
void Compte::asgDescription(const std::string &p_description)
{
  PRECONDITION(!p_description.empty());
  m_description = p_description;
  POSTCONDITION(m_description == p_description);
  INVARIANTS();
}

/**
 * \brief Méthode qui permet de calculer les intérêts d’un compte selon sa spécialisation.
 * \return Par défaut, retourne 0 pour la classe de base.
 */
double Compte::calculerInteret() const
{
  return m_solde * m_tauxInteret;
}
/**
 * \brief Méthode pour obtenir une représentation formatée du compte.
 * \return Une chaîne de caractères représentant le compte.
 */
std::string
Compte::reqCompteFormate() const
{
  std::ostringstream oss;
  oss << "Numero : " << m_noCompte << std::endl;
  oss << "Description : " << m_description << std::endl;
  oss << "Date d'ouverture : " << m_dateOuverture << std::endl;
  oss << "Taux d'interet : " << m_tauxInteret << std::endl;
  oss << "Solde : " << m_solde << " $" << std::endl;
  return oss.str();
}

/**
 * \brief Méthode pour vérifier les invariants de la classe.
 */
void Compte::verifieInvariant() const
{
  INVARIANT(m_noCompte > 0);
  INVARIANT(!m_description.empty());
}
