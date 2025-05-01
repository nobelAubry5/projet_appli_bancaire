/**
 * \file Epargne.cpp
 * \brief Implémentation de la classe Epargne.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#include "Epargne.h"
#include "Compte.h"
#include <sstream>
#include "ContratException.h"

/**
 * \brief Constructeur de la classe Epargne.
 * \param[in] p_noCompte Le numéro de compte.
 * \param[in] p_tauxInteret Le taux d'intérêt du compte.
 * \param[in] p_solde Le solde initial du compte.
 * \param[in] p_description La description du compte.
 * \param[in] p_dateOuverture La date d'ouverture du compte.
 * \pre p_solde doit être positif ou nul
 * \pre p_tauxInteret doit être entre 0.001 et 0.035
 * \post m_description prends la valeur de p_description ou si vide il prends la valeur Épargne
 */
Epargne::Epargne(int p_noCompte,
                 double p_tauxInteret,
                 double p_solde,
                 const util::Date &p_dateOuverture,
                 const std::string &p_description)
    : Compte(p_noCompte, p_tauxInteret, p_solde, p_description.empty() ? "Epargne" : p_description, p_dateOuverture)
{
  PRECONDITION(p_solde >= 0);
  PRECONDITION(p_tauxInteret >= 0.001 && p_tauxInteret <= 0.035);


  // POSTCONDITION (reqDescription () == p_description);
  POSTCONDITION((p_description.empty() && reqDescription() == "Epargne") || (!p_description.empty() && reqDescription() == p_description));

  INVARIANTS();
}

/**
 * \brief Calcule l'intérêt du compte
 * \return Le montant des intérêts calculés
 */
double
Epargne::calculerInteret() const
{
  return reqSolde() * reqTauxInteret();
}

/**
 * \brief Méthode pour créer une copie allouée sur le tas
 * \return Un pointeur unique vers une copie de l'objet courant
 */
std::unique_ptr<bancaire::Compte>
Epargne::clone() const
{
  return std::make_unique<Epargne>(*this);
}

/**
 * \brief Méthode pour obtenir une représentation formatée du compte d'épargne
 * \return Une chaîne de caractères représentant le compte d'épargne
 */
std::string
Epargne::reqCompteFormate() const
{
  std::ostringstream oss;
  oss << "Compte Epargne" << std::endl;
  oss << bancaire::Compte::reqCompteFormate();
  oss << "Interet : " << calculerInteret() << " $" << std::endl;
  return oss.str();
}

/**
 * \brief Méthode pour vérifier les invariants de la classe
 */
void Epargne::verifieInvariant() const
{
  bancaire::Compte::verifieInvariant();
  INVARIANT(reqSolde() >= 0);
  INVARIANT(reqTauxInteret() >= 0.001 && reqTauxInteret() <= 0.035);
}

Epargne::~Epargne() {}
