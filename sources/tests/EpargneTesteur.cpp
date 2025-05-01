/**
 * \file EpargneTesteur.cpp
 * \brief Test unitaire de la classe Epargne
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 05 avril 2025
 */
#include <gtest/gtest.h>
#include "Epargne.h"
#include "ContratException.h"

/**
 * \brief Test du constructeur avec paramètres valides
 * Cas valides: Création d'un objet Epargne avec des valeurs valides et vérification des attributs
 * Cas invalides:
 * - reqSolde le solde est négatif
 * - reqTauxInteret est hors limites (minimum est de 0.1% et au maximum 3.5%)
 *
 */
TEST(EpargneTest, Constructeur_ParametresValides_ObjetValide)
{
  Epargne epargne(567, 0.02, 2500.0, util::Date(29, 12, 1980), std::string("Projets"));
  ASSERT_EQ(567, epargne.reqNoCompte());
  ASSERT_EQ(0.02, epargne.reqTauxInteret());
  ASSERT_EQ(2500.0, epargne.reqSolde());
  ASSERT_EQ("Projets", epargne.reqDescription());
  ASSERT_EQ(util::Date(29, 12, 1980), epargne.reqDateOuverture());
}
/**
 * \brief Test du constructeur avec un solde négatif.
 */
TEST(EpargneTest, Constructeur_SoldeNegatif_PreconditionException)
{
  ASSERT_THROW(
      Epargne(567, 0.02, -50.0, util::Date(29, 12, 1980), std::string("Projets")),
      PreconditionException);
}
/**
 * \brief Test du constructeur avec un taux d'intéret hors-limites.
 */
TEST(EpargneTest, Constructeur_TauxInteretHorsLimites_PreconditionException)
{
  ASSERT_THROW(
      Epargne(567, 0.0005, 2500.0, util::Date(29, 12, 1980), std::string("Projets")),
      PreconditionException);

  ASSERT_THROW(
      Epargne(567, 0.04, 2500.0, util::Date(29, 12, 1980), std::string("Projets")),
      PreconditionException);
}
/**
 * \brief Création d'une fixture utilisé pour les tests de la classe Epargne
 */
class UneEpargne : public ::testing::Test
{
public:
  UneEpargne() : f_epargne(567, 0.02, 2500.0, util::Date(29, 10, 2000), std::string("Projets")) {}
  Epargne f_epargne;
};
/**
 * \brief Test de la méthode calculerInteret()
 * Cas valide : Vérifie que les intérêts sont correctement calculés.
 * Cas invalide : aucun
 */
TEST_F(UneEpargne, CalculerInteret)
{
  ASSERT_EQ(50.0, f_epargne.calculerInteret()); // 2500 * 0.02
}

/**
 * \brief Test de la méthode reqCompteFormate()
 * Cas valide : Vérifie que le format retourné est correct.
 */
TEST_F(UneEpargne, ReqCompteFormate_FormatCorrect)
{
  std::ostringstream oss;
  oss << "Compte Epargne" << std::endl;
  oss << "Numero : " << f_epargne.reqNoCompte() << std::endl;
  oss << "Description : " << f_epargne.reqDescription() << std::endl;
  oss << "Date d'ouverture : " << f_epargne.reqDateOuverture() << std::endl;
  oss << "Taux d'interet : " << f_epargne.reqTauxInteret() << std::endl;
  oss << "Solde : " << f_epargne.reqSolde() << " $" << std::endl;
  oss << "Interet : " << f_epargne.reqSolde() * f_epargne.reqTauxInteret() << " $" << std::endl;

  ASSERT_EQ(f_epargne.reqCompteFormate(), oss.str());
}