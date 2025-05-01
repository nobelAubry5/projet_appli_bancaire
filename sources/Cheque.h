/**
 * \file Cheque.h
 * \brief Classe Cheque, dérivée de la classe Compte.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */
#ifndef CHEQUE_H
#define CHEQUE_H

#include <string>
#include <memory>
#include "Compte.h"

/**
 * \class Cheque
 * \brief Classe dérivée de la classe Compte.
 */
class Cheque : public bancaire::Compte
{
public:
  /**
   * \brief Constructeur avec paramètres
   * \param[in] p_noCompte Numéro du compte
   * \param[in] p_tauxInteret Taux d'intérêt du compte
   * \param[in] p_solde Solde du compte
   * \param[in] p_description Description du compte (par défaut "Cheque")
   * \param[in] p_dateOuverture Date d'ouverture du compte
   * \param[in] p_nombreTransactions Nombre de transactions (par défaut 0)
   * \param[in] p_tauxInteretMinimum Taux d'intérêt minimum (par défaut 0.1%)
   */
  Cheque(int p_noCompte,
         double p_tauxInteret,
         double p_solde,
         const util::Date &p_dateOuverture,
         const std::string &p_description = "Cheque",
         int p_nombreTransactions = 0,
         double p_tauxInteretMinimum = 0.0);

  /**
   * \brief Destructeur virtuel
   */
  virtual ~Cheque() = default;

  /**
   * \brief Accesseur pour le nombre de transactions
   */
  int reqNombreTransactions() const;

  /**
   * \brief Accesseur pour le taux d'intérêt minimum
   */
  double reqTauxInteretMinimum() const;
  
  /**
   * \brief Mutateur pour le taux d'intéret minimum
   * \param[in] p_tauxInteretMinimum Nouveau nombre de transactions
   */
  void asgTauxInteretMinimum(double p_tauxInteretMinimum);

  /**
   * \brief Mutateur pour le nombre de transactions
   * \param[in] p_nombreTransactions Nouveau nombre de transactions
   */
  void asgNombreTransactions(int p_nombreTransactions);

  /**
   * \brief Méthode de clonage (polymorphe)
   * \return Un pointeur unique vers une copie de l'objet
   */
  virtual std::unique_ptr<bancaire::Compte> clone() const override;

  /**
   * \brief Calcule l'intérêt à payer sur le compte
   * \return Le montant d'intérêt à payer
   */
  virtual double calculerInteret() const override;

  /**
   * \brief Formate les informations du compte sous forme de chaîne
   * \return Une chaîne contenant les informations du compte cheque
   */
  std::string reqCompteFormate() const;

private:
  int m_nombreTransactions;
  double m_tauxInteretMinimum;

  /**
   * \brief Vérifie l'invariant de la classe
   */
  void verifieInvariant() const;
};

#endif /* CHEQUE_H */