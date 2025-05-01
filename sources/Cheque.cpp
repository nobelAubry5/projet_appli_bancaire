/**
 * \file Cheque.cpp
 * \brief Implémentation de la classe Cheque.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */
#include "Cheque.h"
#include "Compte.h"
#include <iostream>
#include <sstream>
#include "ContratException.h"
#include <stdexcept>

/**
 * \brief Constructeur de la classe Cheque
 * \param[in] p_noCompte Le numéro de compte.
 * \param[in] p_tauxInteret Le taux d'intérêt du compte.
 * \param[in] p_solde Le solde initial du compte.
 * \param[in] p_description La description du compte.
 * \param[in] p_dateOuverture La date d'ouverture du compte.
 * \pre p_nombreTransactions doit etre supérieur a 0 et ne peut pas dépasser 40 transactions
 * \pre p_tauxInteretMinimum doit etre par défaut de 0.1% et ne pas etre supérieur au taux d'interet du compte
 * \post m_nombreTransactions prends la valeur de p_nombreTransactions
 * \post m_tauxInteretMinimum prends la valeur de p_tauxInteretMinimum
 */
Cheque::Cheque (int p_noCompte, double p_tauxInteret, double p_solde,
                const util::Date &p_dateOuverture, const std::string &p_description,
                int p_nombreTransactions, double p_tauxInteretMinimum)
: bancaire::Compte (p_noCompte, p_tauxInteret, p_solde, p_description.empty () ? "Cheque" : p_description, p_dateOuverture), m_nombreTransactions (p_nombreTransactions), m_tauxInteretMinimum (p_tauxInteretMinimum)
{
  PRECONDITION (p_nombreTransactions >= 0 && p_nombreTransactions <= 40);
  PRECONDITION (p_tauxInteretMinimum >= 0.001 && p_tauxInteretMinimum <= p_tauxInteret);

  POSTCONDITION (m_nombreTransactions == p_nombreTransactions);
  POSTCONDITION (m_tauxInteretMinimum == p_tauxInteretMinimum);

  INVARIANTS ();
}

/**
 * \brief Accesseur pour le nombre de transactions
 * \return Le nombre de transactions
 */
int
Cheque::reqNombreTransactions () const
{
  return m_nombreTransactions;
}

/**
 * \brief Accesseur pour le taux d'intérêt minimum
 * \return Le taux d'intérêt minimum
 */
double
Cheque::reqTauxInteretMinimum () const
{
  return m_tauxInteretMinimum;
}

/**
 * \brief Mutateur pour le taux d'intéret minimum
 */
void
Cheque::asgTauxInteretMinimum (double p_tauxInteretMinimum)
{
  PRECONDITION (p_tauxInteretMinimum >= 0.001 && p_tauxInteretMinimum <= reqTauxInteret ());
  m_tauxInteretMinimum = p_tauxInteretMinimum;
  POSTCONDITION (m_tauxInteretMinimum == p_tauxInteretMinimum);
  verifieInvariant ();
}

/**
 * \brief Mutateur pour le nombre de transactions
 */
void
Cheque::asgNombreTransactions (int p_nombreTransactions)
{
  PRECONDITION (p_nombreTransactions >= 0 && p_nombreTransactions <= 40);
  m_nombreTransactions = p_nombreTransactions;
  POSTCONDITION (m_nombreTransactions == p_nombreTransactions);
  verifieInvariant ();
}

/**
 * \brief Méthode de clonage
 */
std::unique_ptr<bancaire::Compte>
Cheque::clone () const
{
  return std::make_unique<Cheque>(*this);
}

/**
 * \brief Calcule l'intérêt à payer sur le compte
 */
double
Cheque::calculerInteret () const
{
  // solde est positif ou nul, pas d'intérêt à payer
  if (reqSolde () >= 0)
    {
      return 0.0;
    }

  double m_tauxApplique;

  // Déterminer le taux d'intérêt en fonction du nombre de transactions
  if (m_nombreTransactions <= 10)
    {
      m_tauxApplique = m_tauxInteretMinimum;
    }
  else if (m_nombreTransactions <= 25)
    {
      m_tauxApplique = m_tauxInteretMinimum * 1.4; // +40%
    }
  else if (m_nombreTransactions <= 35)
    {
      m_tauxApplique = m_tauxInteretMinimum * 1.8; // +80%
    }
  else
    {
      m_tauxApplique = reqTauxInteret ();
    }

  // Calculer l'intérêt (sur un solde négatif)
  return -reqSolde () * m_tauxApplique / 100.0;
}

/**
 * \brief Formate les informations du compte sous forme de chaîne
 */
std::string
Cheque::reqCompteFormate () const
{
  std::ostringstream oss;
  oss << "Compte Cheque" << std::endl;
  oss << Compte::reqCompteFormate ();
  oss << "nombre de transactions : " << m_nombreTransactions << std::endl;
  oss << "Taux d'interet minimum : " << m_tauxInteretMinimum << std::endl;
  oss << "Interet: " << calculerInteret () << " $" << std::endl;
  return oss.str ();
}

/**
 * \brief Vérifie l'invariant de la classe
 */
void
Cheque::verifieInvariant () const
{
  INVARIANT (m_nombreTransactions >= 0 && m_nombreTransactions <= 40);
  INVARIANT (m_tauxInteretMinimum >= 0.001 && m_tauxInteretMinimum <= reqTauxInteret ());
}
