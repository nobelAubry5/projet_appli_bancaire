/**
 * \file ClientTesteur.cpp
 * \brief Test unitaire de la classe Client
 * \author Aubry Nobel Niyonkuru
 * \version 0.2
 * \date 05 avril 2025
 */

#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Client.h"
#include "Date.h"
#include "Epargne.h"
#include "Cheque.h"
#include "ContratException.h"

/**
 * \test Test du constructeur
 * Cas valides: Creation d’un objet Client et verification de l’assignation de tous les attributs
 */
TEST (ClientTest, ClientTest_constructeur_parDefaut_objetValide)
{
  Client unClient (1542, "aubry", "nobel", "418 456-2526", util::Date (25, 12, 2000));
  ASSERT_EQ (1542, unClient.reqNoFolio ());
  ASSERT_EQ ("aubry", unClient.reqNom ());
  ASSERT_EQ ("nobel", unClient.reqPrenom ());
  ASSERT_EQ ("418 456-2526", unClient.reqTelephone ());
  ASSERT_EQ (util::Date (25, 12, 2000), unClient.reqDateNaissance ());
}

/**
 * \brief Test du constructeur avec un numéro de folio invalide (trop petit).
 */
TEST (ClientTest, Constructeur_NumeroFolioInvalideTropPetit_PreconditionException)
{
  ASSERT_THROW (Client unClient (999, "aubry", "nobel", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un numéro de folio invalide (trop grand).
 */
TEST (ClientTest, Constructeur_NumeroFolioInvalideTropGrand_PreconditionException)
{
  ASSERT_THROW (Client unClient (10001, "aubry", "nobel", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un nom invalide (vide).
 */
TEST (ClientTest, Constructeur_NomInvalideVide_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "", "nobel", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un nom invalide (format invalide).
 */
TEST (ClientTest, Constructeur_NomInvalideFormat_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry1", "nobel", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un prenom invalide (vide).
 */
TEST (ClientTest, Constructeur_PrenomInvalideVide_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry", "", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un prenom invalide (format invalide).
 */
TEST (ClientTest, Constructeur_PrenomInvalideFormat_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry", "nobel1", "418 456-2526", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec un numéro de téléphone invalide (vide).
 */
TEST (ClientTest, Constructeur_NumeroTelephoneInvalide_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry", "nobel", "", util::Date (25, 12, 2000)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec une date de naissance invalide (avant 1970).
 */
TEST (ClientTest, Constructeur_DateNaissanceInvalideTropPetit_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry", "nobel", "418 456-2526", util::Date (25, 12, 1969)),
                PreconditionException);
}

/**
 * \brief Test du constructeur avec une date de naissance invalide (après 2037).
 */
TEST (ClientTest, Constructeur_DateNaissanceInvalideTropGrand_PreconditionException)
{
  ASSERT_THROW (Client unClient (1542, "aubry", "nobel", "418 456-2526", util::Date (25, 12, 2038)),
                PreconditionException);
}

/**
 * \brief Création d'une fixture utilisé pour les tests de la classe Client
 */
class UnClient : public ::testing::Test
{
public:

  UnClient () : f_client (1455, "Joe", "Pelletier", "418 564-2526", util::Date (15, 06, 2010)) { }
  Client f_client;
};

/**
 * \brief Test de la méthode reqNoFolio().
 * Cas valides: reqNoFolio vérifie le retour du numéro de folio du client
 * Cas invalides: aucun.
 */
TEST_F (UnClient, ReqNoFolio_NoFolioValide)
{
  ASSERT_EQ (1455, f_client.reqNoFolio ());
}

/**
 * \brief Test de la méthode reqNom().
 * Cas valides: reqNom vérifie le retour du nom du client
 * Cas invalides: aucun.
 */
TEST_F (UnClient, ReqNom_NomValide)
{
  ASSERT_EQ ("Joe", f_client.reqNom ());
}

/**
 * \brief Test de la méthode reqPrenom().
 * Cas valides: reqPrenom vérifie le retour du prenom du client
 * Cas invalides: aucun.
 */
TEST_F (UnClient, ReqPrenom_PrenomValide)
{
  ASSERT_EQ ("Pelletier", f_client.reqPrenom ());
}

/**
 * \brief Test de la méthode reqTelephone().
 * Cas valides: reqTelephone vérifie le numéro de telephone du client
 * Cas invalides: aucun.
 */
TEST_F (UnClient, ReqTelephone_TelephoneValide)
{
  ASSERT_EQ ("418 564-2526", f_client.reqTelephone ());
}

/**
 * \brief Test de la méthode reqDateNaissance().
 * Cas valides: reqDateNaissance vérifie la date de naissance du client
 * Cas invalides: aucun.
 */
TEST_F (UnClient, ReqDateNaissance_DateNaissanceValide)
{
  ASSERT_EQ (util::Date (15, 06, 2010), f_client.reqDateNaissance ());
}

/**
 * \brief Test de la méthode asgNom() - Cas valide.
 */
TEST_F (UnClient, AsgNom_Valide)
{
  f_client.asgNom ("Gagnon");
  ASSERT_EQ ("Gagnon", f_client.reqNom ());
}

/**
 * \brief Test de la méthode asgPrenom() - Cas valide.
 */
TEST_F (UnClient, AsgPrenom_Valide)
{
  f_client.asgPrenom ("Bob");
  ASSERT_EQ ("Bob", f_client.reqPrenom ());
}

/**
 * \brief Test de la méthode asgTelephone() - Cas valide.
 */
TEST_F (UnClient, AsgTelephone_Valide)
{
  f_client.asgTelephone ("418 418-3212");
  ASSERT_EQ ("418 418-3212", f_client.reqTelephone ());
}

/**
 * \brief Test de la méthode ajouterCompte().
 */
TEST_F (UnClient, AjouterCompte)
{
  std::unique_ptr<bancaire::Compte> compte1 = std::make_unique<Epargne>(201, 0.02, 1000.0, util::Date (1, 1, 2025), "Epargne 1");
  f_client.ajouterCompte (*compte1);
}

/**
 * \brief Test de la méthode reqReleves().
 */
TEST_F (UnClient, ReqReleves_RelevesValide)
{
  std::ostringstream oss;
  oss << "Client no de folio : " << f_client.reqNoFolio () << std::endl;
  oss << f_client.reqPrenom () << " " << f_client.reqNom () << std::endl;
  oss << "Date de naissance: " << f_client.reqDateNaissance () << std::endl;
  oss << f_client.reqTelephone () << std::endl;
  oss << std::endl;
  ASSERT_EQ (oss.str (), f_client.reqReleves ());
}

/**
 * \brief Test de la méthode reqClientFormate().
 */
TEST_F (UnClient, ReqClientFormate__FormatValide)
{
  std::ostringstream oss;
  oss << "Client no de folio : " << f_client.reqNoFolio () << std::endl;
  oss << f_client.reqPrenom () << " " << f_client.reqNom () << std::endl;
  oss << "Date de naissance: " << f_client.reqDateNaissance () << std::endl;
  oss << f_client.reqTelephone () << std::endl;
  ASSERT_EQ (oss.str (), f_client.reqClientFormate ());
}