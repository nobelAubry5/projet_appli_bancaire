/**
 * \file CompteTesteur.cpp
 * \brief Test unitaire de la classe Compte
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 05 avril 2025
 */

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "Compte.h"
#include "Epargne.h"
#include "Date.h"
#include "ContratException.h"

using namespace std;
using namespace bancaire;
using namespace util;

class CompteDeTest : public Compte
{
public:

  CompteDeTest (int p_noCompte, double p_tauxInteret, double p_solde, const std::string& p_description, const util::Date& p_dateOuverture) : Compte (p_noCompte, p_tauxInteret, p_solde, p_description, p_dateOuverture) { }

  virtual double
  calculerInteret () const override
  {
    return reqSolde () * reqTauxInteret ();
  }

  virtual std::unique_ptr<Compte>
  clone () const override
  {
    return std::make_unique<CompteDeTest>(*this);
  }
};

/**
 * \brief Test du constructeur avec paramètres
 * Cas valides: Création d'un objet Compte avec des valeurs valides
 * et vérification de tous les attributs.
 * Cas invalides: constructeurParametreInvalide
 * - Numéro de compte non positif.
 * - Description vide.
 */
TEST (Compte, CompteTest_constructeur_parDefaut_objetValide)
{
  CompteDeTest c1 (1, 0.02, 500.0, "Compte courant", util::Date (15, 06, 1975));
  ASSERT_EQ (001, c1.reqNoCompte ());
  ASSERT_EQ (0.02, c1.reqTauxInteret ());
  ASSERT_EQ (500.0, c1.reqSolde ());
  ASSERT_EQ ("Compte courant", c1.reqDescription ());
  ASSERT_EQ (util::Date (15, 06, 1975), c1.reqDateOuverture ());
}

/**
 * \brief Test du constructeur avec un numéro de compte invalide (négatif ou 0).
 */
TEST (Compte, constructeur_NumeroCompteInvalide_PreconditionException)
{
  ASSERT_THROW (CompteDeTest (-1, 0.02, 500.0, "Compte courant", util::Date (15, 06, 1975)), PreconditionException);

  ASSERT_THROW (CompteDeTest (0, 0.02, 500.0, "Compte courant", util::Date (15, 06, 1975)), PreconditionException);
}

/**
 * \brief Test du constructeur avec une description invalide (vide).
 */
TEST (Compte, constructeur_DescriptionInvalide_PreconditionException)
{
  ASSERT_THROW (CompteDeTest (1, 0.02, 500.0, "", util::Date (15, 06, 1975)), PreconditionException);
}

/**
 * \brief Création d'une fixture utilisé pour les tests de la classe Compte
 */
class UnCompte : public ::testing::Test
{
public:

  UnCompte () : f_compte (12100, 0.025, 1500.0, "Compte epargne", util::Date (25, 04, 2020)) { }
  CompteDeTest f_compte;
};

/**
 * \brief Test de la méthode reqNoCompte();
 * Cas valides: reqNoCompte vérifier le retour du numéro de compte
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqNoCompte_NoCompteValide)
{
  ASSERT_EQ (12100, f_compte.reqNoCompte ());
}

/**
 * \brief Test de la méthode reqTauxInteret();
 * Cas valides: reqTauxInteret vérifier le retour du taux d'intérêt.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqTauxInteret_TauxInteretValide)
{
  ASSERT_EQ (0.025, f_compte.reqTauxInteret ());
}

/**
 * \brief Test de la méthode reqSolde();
 * Cas valides: reqSolde vérifier le retour du solde.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqSolde_SoldeValide)
{
  ASSERT_EQ (1500.0, f_compte.reqSolde ());
}

/**
 * \brief Test de la méthode reqDescription();
 * Cas valides: reqDescription vérifier le retour de la description.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqDescription_DescriptionValide)
{
  ASSERT_EQ ("Compte epargne", f_compte.reqDescription ());
}

/**
 * \brief Test de la méthode reqDateOuverture();
 * Cas valides: reqDateOuverture vérifier le retour de la date d'ouverture.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqDateOuverture_DateOuvertureValide)
{
  ASSERT_EQ (util::Date (25, 04, 2020), f_compte.reqDateOuverture ());
}

/**
 * \brief Test de la méthode calculerInteret();
 * Cas valide: Vérifier le retour de 0
 */
TEST_F (UnCompte, calculerInteret)
{
  ASSERT_EQ (f_compte.reqSolde () * f_compte.reqTauxInteret (), f_compte.calculerInteret ());
}

/**
 * \brief Test de la méthode mutateur asgTauxInteret();
 * Cas valides: asgTauxInteret assigne un nouveau taux d'intéret au compte.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, AsgTauxInteret_Valide)
{
  f_compte.asgTauxInteret (0.035);
  ASSERT_EQ (0.035, f_compte.reqTauxInteret ());
}

/**
 * \brief Test de la méthode mutateur asgSolde();
 * Cas valides: asgSolde assigne un nouveau solde au compte.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, AsgSolde_Valide)
{
  f_compte.asgSolde (3500.0);
  ASSERT_EQ (3500.0, f_compte.reqSolde ());
}

/**
 * \brief Test de la méthode mutateur asgDescription();
 * Cas valides: asgDescription assigne une description au compte.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, AsgDescription_Valide)
{
  f_compte.asgDescription ("Compte courant");
  ASSERT_EQ ("Compte courant", f_compte.reqDescription ());
}

/**
 * \brief Test de la méthode reqCompteFormate();
 * Cas valides: reqCompteFormate vérifier le format du compte.
 * Cas invalides: aucun.
 */
TEST_F (UnCompte, ReqCompteFormate__FormatValide)
{
  std::ostringstream oss;
  oss << "Numero : " << f_compte.reqNoCompte () << std::endl;
  oss << "Description : " << f_compte.reqDescription () << std::endl;
  oss << "Date d'ouverture : " << f_compte.reqDateOuverture () << std::endl;
  oss << "Taux d'interet : " << f_compte.reqTauxInteret () << std::endl;
  oss << "Solde : " << f_compte.reqSolde () << " $" << std::endl;
  oss << "Interet : " << f_compte.calculerInteret () << " $" << std::endl;

  ASSERT_EQ (oss.str (), f_compte.reqCompteFormate ());
}
