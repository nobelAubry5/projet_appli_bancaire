/**
 * \file Patron.h
 * \brief Classe Client.
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 8 mars 2025
 */

#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include <memory>
#include "ContratException.h"
#include "Compte.h"
#include "Date.h"

/**
 * \class Client
 * \brief Classe modélisant la gestion des comptes.
 */
class Client
{
public:
  /**
   * \brief Constructeur de la classe Client
   * \param[in] p_noFolio Le numéro de folio du client
   * \param[in] p_nom Le nom du client
   * \param[in] p_prenom Le prénom du client
   * \param[in] p_telephone Le numéro de téléphone du client
   */
  Client(int p_noFolio, const std::string &p_nom, const std::string &p_prenom,
         const std::string &p_telephone, const util::Date &p_dateNaissance);

  /**
   * \brief Destructeur de la classe Client
   */
  ~Client();

  /**
   * \brief Constructeur copie de la classe Client.
   */
  Client(const Client &p_client);

  /**
   * \brief Opérateur d'assignation de la classe Client.
   */
  Client &operator=(const Client &p_client);
  /**
   * \brief Méthode accesseur pour obtenir le numéro de folio du client
   * \return Le numéro de folio du client
   */
  int reqNoFolio() const;
  /**
   * \brief Méthode accesseur pour obtenir le nom du client
   * \return Le nom du client
   */
  std::string reqNom() const;

  /**
   * \brief Méthode accesseur pour obtenir le prénom du client
   * \return Le prénom du client
   */
  std::string reqPrenom() const;

  /**
   * \brief Méthode accesseur pour obtenir le numéro de téléphone du client
   * \return Le numéro de téléphone du client
   */
  std::string reqTelephone() const;

  /**
   * \brief Accesseur pour la date de naissance
   * \return La date de naissance du client
   */
  const util::Date &reqDateNaissance() const;
  /**
   * \brief Méthode mutateur pour modifier le nom du client
   * \param[in] p_nom Le nouveau nom du client
   */
  void asgNom(const std::string &p_nom);

  /**
   * \brief Méthode mutateur pour modifier le prénom du client
   * \param[in] p_prenom Le nouveau prénom du client
   */
  void asgPrenom(const std::string &p_prenom);

  /**
   * \brief Méthode mutateur pour modifier le numéro de téléphone du client
   * \param[in] p_telephone Le nouveau numéro de téléphone du client
   */
  void asgTelephone(const std::string &p_telephone);

  /**
   * \brief Méthode pour valider le format du nom et du prénom.
   */
  static bool validerFormatNom(const std::string &p_nom);

  /**
   * \brief Méthode pour ajouter un compte au client.
   */
  void ajouterCompte(const bancaire::Compte &p_nouveauCompte);

  /**
   * \brief Méthode pour obtenir une représentation formatée du client
   * \return Une chaîne de caractères représentant le client
   */
  std::string reqClientFormate() const;

  /**
   * \brief Méthode pour obtenir le relevé de tous les comptes du client.
   * \return Une chaîne de caractères représentant les informations du client et des ses comptes
   */
  std::string reqReleves() const;

private:
  int m_noFolio;
  std::string m_nom;
  std::string m_prenom;
  std::string m_telephone;
  util::Date m_dateNaissance;

  std::vector<std::unique_ptr<bancaire::Compte>> m_comptes;

  void verifieInvariant() const;
};

#endif /* CLIENT_H */
