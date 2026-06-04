#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit ) {
    _accountIndex = _nbAccounts;
    _amount = initial_deposit;
    _nbAccounts += 1;
    _totalAmount += initial_deposit;

    Account::_displayTimestamp();
    std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account( void ) {
    Account::_displayTimestamp();
    std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

void	Account::makeDeposit( int deposit ) {
    _amount += deposit;
    _nbDeposits += 1;
    _totalAmount += deposit;
    _totalNbDeposits += 1;

    Account::_displayTimestamp();
    std::cout << " index:" << _accountIndex << ";p_amount:" << _amount - deposit << ";deposit:" << deposit
              << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal ) {
    if (withdrawal > _amount) {
        Account::_displayTimestamp();
        std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";withdrawal:refused" << std::endl;
        return (false);
    }
    _amount -= withdrawal;
    _nbWithdrawals += 1;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals += 1;

    Account::_displayTimestamp();
    std::cout << " index:" << _accountIndex << ";p_amount:" << _amount + withdrawal << ";withdrawal:" << withdrawal
              << ";amount:" << _amount << ";nb_withdrawal:" << _nbWithdrawals << std::endl;
    return (true);
}

int Account::checkAmount( void ) const {
    return (_amount);
}

void    Account::displayStatus( void ) const {
    Account::_displayTimestamp();
    std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals << std::endl;
}

int	Account::getNbAccounts( void ) {
    return (_nbAccounts);
}

int	Account::getTotalAmount( void ) {
    return (_totalAmount);
}

int	Account::getNbDeposits( void ) {
    return (_totalNbDeposits);
}

int Account::getNbWithdrawals( void ) {
    return (_totalNbWithdrawals);
}

void    Account::displayAccountsInfos( void ) {
    Account::_displayTimestamp();
    std::cout << " accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void    Account::_displayTimestamp( void ) {
    time_t  dateInSeconds = time(NULL);
    tm      *dateGoodFormat = localtime(&dateInSeconds);
    char    dateToDisplay[50];
    strftime(dateToDisplay, sizeof(dateToDisplay), "[%Y%m%d_%H%M%S]", dateGoodFormat);
    std::cout << dateToDisplay;
}
