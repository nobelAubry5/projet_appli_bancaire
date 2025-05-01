/**
 * \file Cheque.cpp
 * \brief Test unitaire de la classe Cheque
 * \author Aubry Nobel Niyonkuru
 * \version 0.1
 * \date 05 avril 2025
 */
#include <gtest/gtest.h>
#include "Cheque.h"
#include "ContratException.h"

/**
 * \brief Test du constructeur avec paramètres valides
 * Cas valide : Création d'un objet Cheque avec des valeurs valides et vérification des attributs.
 * Cas invalide:
 * - reqNombreTransactions : Le nombre de transactions est plus grand que 40 
 */
TEST(ChequeTest, Constructeur_ParametresValides_ObjetValide)
{
  Cheque cheque(12345, 4.2, -3000.0, util::Date(29, 12, 1980), std::string("Mon compte courant"), 4, 0.3);
  ASSERT_EQ(12345, cheque.reqNoCompte());
  ASSERT_EQ(4.2, cheque.reqTauxInteret());
  ASSERT_EQ(-3000.0, cheque.reqSolde());
  ASSERT_EQ("Mon compte courant", cheque.reqDescription());
  ASSERT_EQ(util::Date(29, 12, 1980), cheque.reqDateOuverture());
}
/**
 * \brief Test du constructeur avec le nombre de transactions invalides.
 */
TEST(ChequeTest, Constructeur_NombreTransactionsInvalide_PreconditionException)
{
  ASSERT_THROW(
      Cheque(12345, 4.2, -3000.0, util::Date(29, 12, 1980), std::string("Mon compte courant"), 41, 0.3),
      PreconditionException);
}
/**
 * \brief Test du constructeur avec un taux d'intéret minimum hors-limites.
 */
TEST(ChequeTest, Constructeur_TauxInteretMinimumInvalide_PreconditionException)
{
  ASSERT_THROW(
      Cheque(12345, 4.2, -3000.0, util::Date(29, 12, 1980), std::string("Mon compte courant"), 4, 5.0),
      PreconditionException);
}
/**
 * \brief Création d'une fixture utilisé pour les tests de la classe Cheque
 */
class UnCheque : public ::testing::Test
{
public:
  UnCheque() : f_cheque(12345, 4.2, -3000.0, util::Date(29, 10, 2002), std::string("Mon compte courant"), 4, 0.3) {}
  Cheque f_cheque;
};

/**
 * \brief Test de la méthode calculerInteret()
 * Cas valide : Vérifie que les intérêts sont correctement calculés en fonction du nombre de transactions.
 */
TEST_F(UnCheque, CalculerInteret_CalculValide)
{
  // Cas 1 : Nombre de transactions entre 0 et 10
  f_cheque.asgNombreTransactions(5);
  ASSERT_EQ(9.0, f_cheque.calculerInteret());

  // Cas 2 : Nombre de transactions entre 11 et 25
  f_cheque.asgNombreTransactions(15);
  ASSERT_EQ(12.6, f_cheque.calculerInteret());

  // Cas 3 : Nombre de transactions entre 26 et 35
  f_cheque.asgNombreTransactions(30);
  ASSERT_EQ(16.2, f_cheque.calculerInteret());

  // Cas 4 : Nombre de transactions au-delà de 35
  f_cheque.asgNombreTransactions(40);
  ASSERT_EQ(126.0, f_cheque.calculerInteret());
}

/**
 * \brief Test de la méthode reqCompteFormate()
 * Cas valide : Vérifie que le format retourné est correct.
 */
TEST_F(UnCheque, ReqCompteFormate_FormatValide)
{
  std::ostringstream oss;
  oss << "Compte Cheque" << std::endl;
  oss << "Numero : " << f_cheque.reqNoCompte() << std::endl;
  oss << "Description : " << f_cheque.reqDescription() << std::endl;
  oss << "Date d'ouverture : " << f_cheque.reqDateOuverture() << std::endl;
  oss << "Taux d'interet : " << f_cheque.reqTauxInteret() << std::endl;
  oss << "Solde : " << f_cheque.reqSolde() << " $" << std::endl;
  oss << "nombre de transactions : " << f_cheque.reqNombreTransactions() << std::endl;
  oss << "Taux d'interet minimum : " << f_cheque.reqTauxInteretMinimum() << std::endl;
  
  double m_tauxApplique;
    if (f_cheque.reqNombreTransactions() <= 10)
    {
        m_tauxApplique = f_cheque.reqTauxInteretMinimum();
    }
    else if (f_cheque.reqNombreTransactions() <= 25)
    {
        m_tauxApplique = f_cheque.reqTauxInteretMinimum() * 1.4;
    }
    else if (f_cheque.reqNombreTransactions() <= 35)
    {
        m_tauxApplique = f_cheque.reqTauxInteretMinimum() * 1.8;
    }
    else
    {
        m_tauxApplique = f_cheque.reqTauxInteret();
    }
  oss << "Interet: " << -f_cheque.reqSolde() * m_tauxApplique / 100.0 << " $" << std::endl;
  ASSERT_EQ(f_cheque.reqCompteFormate(), oss.str());
}