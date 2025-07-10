#include "Player.h"
#include "Range.h"
Player::Player(const std::string &name,
               std::unique_ptr<Job> &&job,
               std::unique_ptr<Character> &&character,
               std::unique_ptr<Range> &&range)
        : m_force(INITIAL_FORCE),
          m_coins(job->getCoins()),
          m_level(INITIAL_LEVEL),
          m_HP(job->getMaxHP()),
          m_maxHP(job->getMaxHP()),
          m_name(name),
          m_job(std::move(job)),
          m_character(std::move(character)),
          m_range(std::move(range))
{}

void Player::levelUp() {
    if (m_level == MAX_LEVEL) {
        return;
    }

    m_level++;
}

int Player::getLevel() const {
    return m_level;
}

void Player::changeForce(int force) {
    m_force = m_force+force;
    if (m_force < 0)
        m_force = MIN_FORCE;
}

void Player::damage(int HP) {
    m_HP = m_HP-HP;
    if (m_HP < 0) m_HP = MIN_HP;
}

bool Player::isKnockedOut() const {
    if (m_HP == MIN_HP) {
        return true;
    }
    return false;
}

void Player::addCoins(int coins) {
    m_coins= m_coins+ coins;
}

void Player::buy_and_apply() {
    m_coins -= 5;

    m_HP  += 10;
    if (m_HP == m_maxHP) {
        m_HP = 100;
    }
}

int Player::getCombatPower() const {
    return m_job->getCombatPower(m_force,m_level);
}

std::string Player::getName() const {
    return this->m_name;
}

int Player::getCoins() const {
    return m_coins;
}

int Player::getForce() const {
    return m_force;
}

int Player::getHealthPoints() const {
    return m_HP;
}

Character* Player::getCharacter() {
    return m_character.get();
}

void Player::setCharacter(unique_ptr<Character> character) {
    m_character = std::move(character);
}

string Player::getRange() {
    return m_range->getRange();
}


int Player::getMaxHP() const {
    return m_maxHP;
}

string Player::getDescription() const {
    return m_name + ", " + m_job->getJob() + " with "  + m_character->getCharacter() + " character " + "(level " +std::to_string(m_level)
           + ", force " +std::to_string(m_force) +  ")";
}
void Player::setJob(unique_ptr<Job> job) {
    m_job = std::move(job);

}
Job* Player::getJob() const {
    return m_job.get();
}
bool Player::isAlive() const {
    return m_HP > 0;
}