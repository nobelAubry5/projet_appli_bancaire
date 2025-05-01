/**
 * \file Compte.h
 * \brief Classe de base abstraite Compte.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#ifndef COMPTE_H
#define COMPTE_H

#include <string>
#include <vector>
#include <memory>
#include "Date.h"

namespace bancaire
{
  /**
   * \class Compte
   * \brief Classe modélisant tous les types de comptes d’un client.
   */
  class Compte
  {
  public:
    /**
     * \brief Constructeur avec paramètres
     * \param[in] p_noCompte Numéro du compte
     * \param[in] p_tauxInteret Taux d'intérêt du compte
     * \param[in] p_solde Solde du compte
     * \param[in] p_description Description du compte
     * \param[in] p_dateOuverture Date d'ouverture du compte
     */
    Compte(int p_noCompte, double p_tauxInteret, double p_solde, const std::string &p_description, const util::Date &p_dateOuverture);

    /**
     * \brief Destructeur virtuel
     */
    virtual ~Compte();

    /**
     * \brief Accesseur pour le numéro de compte
     */
    int reqNoCompte() const;
    /**
     * \brief Accesseur pour le taux d'intérêt
     */
    double reqTauxInteret() const;
    /**
     * \brief Accesseur pour le solde
     */
    double reqSolde() const;
    /**
     * \brief Accesseur pour la description
     */
    std::string reqDescription() const;
    /**
     * \brief Accesseur pour la date d'ouverture
     */
    const util::Date &reqDateOuverture() const;

    /**
     * \brief Mutateur pour le taux d'intérêt
     * \param[in] p_tauxInteret Nouveau taux d'intérêt
     */
    void asgTauxInteret(double p_tauxInteret);
    /**
     * \brief Mutateur pour le solde
     * \param p_solde Nouveau solde
     */
    void asgSolde(double p_solde);
    /**
     * \brief Mutateur pour la description
     * \param p_description Nouvelle description
     */
    void asgDescription(const std::string &p_description);

    /**
     * \brief Méthode de clonage pour créer une copie du compte
     */
    virtual std::unique_ptr<Compte> clone() const = 0;

    /**
     * \brief Méthode virtuelle qui calcule l'intérêt à payer sur le compte
     */
    virtual double calculerInteret() const;

    /**
     * \brief Méthode qui formate les informations du compte sous forme de chaîne
     */
    std::string reqCompteFormate() const;

  private:
    int m_noCompte;
    double m_tauxInteret;
    double m_solde;
    std::string m_description;
    util::Date m_dateOuverture;

  protected:
    void verifieInvariant() const;
  };
}

#endif /* COMPTE_H */
