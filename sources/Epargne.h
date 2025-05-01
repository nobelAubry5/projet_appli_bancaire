/**
 * \file Epargne.h
 * \brief Classe Epargne, dérivée de la classe Compte.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#ifndef EPARGNE_H
#define EPARGNE_H
#include <string>
#include "Compte.h"
#include "ContratException.h"

/**
 * \class Epargne
 * \brief Classe dérivée de la classe Compte
 */
class Epargne : public bancaire::Compte
{
public:
  /**
   * \brief Constructeur de la classe Epargne
   * \param[in] p_noCompte Le numéro de compte
   * \param[in] p_tauxInteret Le taux d'intérêt du compte (entre 0.001 et 0.035)
   * \param[in] p_solde Le solde initial du compte (doit être positif ou nul)
   * \param[in] p_description La description du compte, "Epargne" par défaut
   * \param[in] p_dateOuverture La date d'ouverture du compte
   */
  Epargne(int p_noCompte,
          double p_tauxInteret,
          double p_solde,
          const util::Date &p_dateOuverture,
          const std::string &p_description = "Epargne");
  /**
   * \brief Destructeur virtuel de la classe Epargne
   */
  virtual ~Epargne();
  /**
   * \brief Calcule l'intérêt du compte
   * \return Le montant des intérêts calculés
   */
  double calculerInteret() const;

  /**
   * \brief Méthode pour créer une copie allouée sur le tas
   * \return Un pointeur unique vers une copie de l'objet courant
   */
  std::unique_ptr<Compte> clone() const;

  /**
   * \brief Méthode pour obtenir une représentation formatée du compte d'épargne
   * \return Une chaîne de caractères représentant le compte d'épargne
   */
  std::string reqCompteFormate() const;

private:
    void verifieInvariant() const;
};

#endif /* EPARGNE_H */
