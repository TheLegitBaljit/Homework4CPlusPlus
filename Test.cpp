#include "sources/Character.hpp"
#include "sources/Cowboy.hpp"
#include "sources/OldNinja.hpp"
#include "sources/Point.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "doctest.h"

using namespace doctest;

TEST_CASE("Testing character creation")
{
    Point point(0, 0);
    Cowboy dummy("dummy",Point(15,0));
    SUBCASE("Creating a Cowboy") {
        Cowboy cowboy("John", point);
        CHECK(cowboy.getName() == "John");
        CHECK(cowboy.getLocation() == point);
        CHECK(cowboy.isAlive() == true);
        for (int i = 0; i < 5; ++i) {
            cowboy.shoot(nullptr);
        }
        CHECK(cowboy.hasboolets());
        cowboy.shoot(nullptr);
        CHECK(cowboy.hasboolets() == false);
        CHECK(cowboy.getHitPoints() == 110);
    }

    SUBCASE("Creating a YoungNinja") {
        YoungNinja youngNinja("Hiro", point);
        CHECK(youngNinja.getName() == "Hiro");
        CHECK(youngNinja.getLocation() == point);
        CHECK(youngNinja.isAlive() == true);
        CHECK(youngNinja.getHitPoints() == 100);
        CHECK_NOTHROW(youngNinja.move(&dummy));
        CHECK(youngNinja.getLocation() == Point(14,0));
    }

    SUBCASE("Creating a TrainedNinja") {
        TrainedNinja trainedNinja("Takeshi", point);
        CHECK(trainedNinja.getName() == "Takeshi");
        CHECK(trainedNinja.getLocation() == point);
        CHECK(trainedNinja.isAlive() == true);
        CHECK(trainedNinja.getHitPoints() == 120);
        CHECK_NOTHROW(trainedNinja.move(&dummy));
        CHECK(trainedNinja.getLocation() == Point(12,0));
    }

    SUBCASE("Creating an OldNinja") {
        OldNinja oldNinja("Jiro", point);
        CHECK(oldNinja.getName() == "Jiro");
        CHECK(oldNinja.getLocation() == point);
        CHECK(oldNinja.isAlive() == true);
        CHECK_NOTHROW(oldNinja.move(&dummy));
        CHECK(oldNinja.getLocation() == Point(8,0));
    }
}

TEST_CASE("Testing Cowboy class") {
    Cowboy cowboy("Cowboy", Point(0, 0));
    CHECK(cowboy.print() == "C Cowboy (0,0) 110");

    Character enemy(Point(1, 1), 10, "Enemy");
    cowboy.shoot(&enemy);
    CHECK(enemy.isAlive() == false);
    CHECK(enemy.print() == "Enemy (1,1)");

    SUBCASE("Testing shoot method") {
        Cowboy c("John", Point(0, 0));
        Cowboy c2("Mike", Point(0, 0));
        c.shoot(&c2);
        CHECK(c2.isAlive() == true);
        CHECK(c.getName() == "John");
        CHECK(c.hasboolets() == true);

    }
    Point location(1.0, 2.0);
    Cowboy c("John", location);

    SUBCASE("Testing isAlive method") {
        CHECK(c.isAlive() == true);
        c.hit(110);
        CHECK(c.isAlive() == false);
    }

    SUBCASE("Testing distance method") {
        Point location2(3.0, 4.0);
        Cowboy c2("Mike", location2);
        double dist = c.distance(&c2);
        CHECK(dist == doctest::Approx(2.8284).epsilon(0.001));
    }

    SUBCASE("Testing shoot method") {
        Point location2(3.0, 4.0);
        Character c2(location2, 10, "Mike");
        c.reload();
        c.shoot(&c2);
        CHECK(c2.isAlive() == false);
        CHECK(c.hasboolets() == true);
    }

    SUBCASE("Testing hasboolets and reload methods") {
        CHECK_THROWS(c.shoot(&c));
        c.reload();
        CHECK(c.hasboolets() == true);
    }
}

TEST_CASE("Testing Ninja classes") {
    OldNinja oldNinja("Old Ninja", Point(0, 0));
    TrainedNinja trainedNinja("Trained Ninja", Point(0, 0));
    YoungNinja youngNinja("Young Ninja", Point(0, 0));

    CHECK(oldNinja.print() == "N Old Ninja (0,0) 150");
    CHECK(trainedNinja.print() == "N Trained Ninja (0,0) 120");
    CHECK(youngNinja.print() == "N Young Ninja (0,0) 100");

    Character enemy(Point(0.5, 0), 100, "Enemy");
    oldNinja.slash(&enemy);
    CHECK(enemy.print() == "Enemy (0.5,0) 69");
}

TEST_CASE("Testing Team class") {
    Cowboy leader("Leader", Point(0, 0));
    Team team(&leader);
    team.add(new TrainedNinja("Trained Ninja", Point(0, 0)));
    team.add(new YoungNinja("Young Ninja", Point(0, 0)));

    CHECK(team.stillAlive() == 3);

    Cowboy enemyLeader("Enemy Leader", Point(3, 4));
    Team enemyTeam(&enemyLeader);
    enemyTeam.add(new OldNinja("Old Ninja", Point(3, 4)));

    team.attack(&enemyTeam);
    CHECK(enemyLeader.print() != "Enemy Leader (3,4) 110");
}

TEST_CASE("Team attack method") {
    SUBCASE("Team attacking other Team") {
        Cowboy c1("c1", Point(0, 0));
        Cowboy c2("c2", Point(0, 0));
        Cowboy c3("c3", Point(0, 0));
        Cowboy c4("c4", Point(0, 0));

        Team t1(&c1);
        t1.add(&c2);
        t1.add(&c3);
        t1.add(&c4);

        Cowboy d1("d1", Point(0, 0));
        Cowboy d2("d2", Point(1, 1));
        Cowboy d3("d3", Point(2, 2));
        Cowboy d4("d4", Point(3, 3));

        Team t2(&d1);
        t2.add(&d2);
        t2.add(&d3);
        t2.add(&d4);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d2.isAlive() == false);
        CHECK(d2.print() == "C (d2) (1,1)");
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d3.isAlive() == false);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d4.isAlive() == false);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d1.isAlive() == false);
    }
    SUBCASE("Team attacking Team2")
    {
        Cowboy c1("c1", Point(0, 0));
        Cowboy c2("c2", Point(0, 0));
        Cowboy c3("c3", Point(0, 0));
        Cowboy c4("c4", Point(0, 0));

        Team t1(&c1);
        t1.add(&c2);
        t1.add(&c3);
        t1.add(&c4);

        Cowboy d1("d1", Point(0, 0));
        Cowboy d2("d2", Point(1, 1));
        Cowboy d3("d3", Point(2, 2));
        Cowboy d4("d4", Point(3, 3));

        Team2 t2(&d1);
        t2.add(&d3);
        t2.add(&d4);
        t2.add(&d2);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d2.isAlive() == false);
        CHECK(d2.print() == "C (d2) (1,1)");
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d3.isAlive() == false);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d4.isAlive() == false);
        for (int i = 0; i < 3; ++i) {
            t1.attack(&t2);
        }
        CHECK(d1.isAlive() == false);

    }
    SUBCASE("Team attacks the character closest to the leader in another Team, reducing the target's hit points") {
        Team attackingTeam(new Cowboy("Cowboy1", Point(0, 0)));
        Team targetTeam(new Cowboy("TargetCowboy1", Point(10, 10)));

        YoungNinja ninja1("Ninja1", Point(1, 1));
        Cowboy targetCowboy2("TargetCowboy2", Point(11, 11));

        attackingTeam.add(&ninja1);
        targetTeam.add(&targetCowboy2);

        int initialLivingMembers = targetTeam.stillAlive();
        attackingTeam.attack(&targetTeam);
        int livingMembersAfterAttack = targetTeam.stillAlive();

        CHECK(livingMembersAfterAttack <= initialLivingMembers);
    }
    SUBCASE("Dead team tries to attack another team") {
        Cowboy deadCowboy1("DeadCowboy1", Point(0, 0));
        deadCowboy1.hit(110);
        Team attackingTeam(&deadCowboy1);
        Cowboy deadCowboy2("DeadCowboy2", Point(1, 1));

        // Set hit points to 0, making the characters dead
        deadCowboy2.hit(110);
        attackingTeam.add(&deadCowboy2);

        Team targetTeam(new Cowboy("TargetCowboy1", Point(10, 10)));
        YoungNinja targetNinja("TargetNinja1", Point(11, 11));
        targetTeam.add(&targetNinja);

        int initialLivingMembers = targetTeam.stillAlive();
        attackingTeam.attack(&targetTeam);
        int livingMembersAfterAttack = targetTeam.stillAlive();

        // Check that the number of living members in the target team has not changed (dead team can't attack)
        CHECK(livingMembersAfterAttack == initialLivingMembers);
    }
    SUBCASE("Attacking Teams attack a dead Team")
    {
        Cowboy c1("c1", Point(0, 0));
        Cowboy c2("c2", Point(0, 0));
        Cowboy c3("c3", Point(0, 0));
        Cowboy c4("c4", Point(0, 0));

        Team t1(&c1);
        t1.add(&c2);
        t1.add(&c3);
        t1.add(&c4);

        Cowboy d1("d1", Point(0, 0));
        Cowboy d2("d2", Point(1, 1));
        Cowboy d3("d3", Point(2, 2));
        Cowboy d4("d4", Point(3, 3));

        d1.hit(d1.getHitPoints());
        d2.hit(d2.getHitPoints());
        d3.hit(d3.getHitPoints());
        d4.hit(d4.getHitPoints());

        Team2 t2(&d1);
        t2.add(&d3);
        t2.add(&d4);
        t2.add(&d2);

        CHECK_NOTHROW(t1.attack(&t2));
    }
    SUBCASE("Team attacks another team, but no damage is done due to distance") {
        Team attackingTeam(new TrainedNinja("leader", Point(0, 0)));
        YoungNinja ninja1("Ninja1", Point(1, 1));
        attackingTeam.add(&ninja1);

        Team targetTeam(new Cowboy("TargetCowboy1", Point(1000, 1000)));
        YoungNinja targetNinja("TargetNinja1", Point(1001, 1001));
        targetTeam.add(&targetNinja);

        int initialAttackingTeamLivingMembers = attackingTeam.stillAlive();
        int initialTargetTeamLivingMembers = targetTeam.stillAlive();

        attackingTeam.attack(&targetTeam);

        int livingMembersAfterAttackInAttackingTeam = attackingTeam.stillAlive();
        int livingMembersAfterAttackInTargetTeam = targetTeam.stillAlive();

        CHECK(livingMembersAfterAttackInAttackingTeam == initialAttackingTeamLivingMembers);
        CHECK(livingMembersAfterAttackInTargetTeam == initialTargetTeamLivingMembers);
    }
    SUBCASE("Simulate attack between two teams and check if one team is defeated") {
        Team team1(new Cowboy("Cowboy1", Point(0, 0)));
        YoungNinja youngNinja("YoungNinja1", Point(1, 1));
        team1.add(&youngNinja);

        Team team2(new Cowboy("Cowboy2", Point(200, 200)));
        TrainedNinja trainedNinja("TrainedNinja1", Point(300, 300));
        team2.add(&trainedNinja);

        int maxRounds = 300;
        int round = 0;

        // Simulate a series of attacks until one team is defeated or maxRounds is reached
        while (team1.stillAlive() > 0 && team2.stillAlive() > 0 && round < maxRounds) {
            team1.attack(&team2);
            team2.attack(&team1);
            round++;
        }

        // Check if one of the teams has been defeated
        bool flag = ((team1.stillAlive() == 0) || (team2.stillAlive() == 0));
        CHECK(flag == true);
    }
    SUBCASE("Simulate a more complex attack between two teams and check if one team is defeated") {
        Team team1(new Cowboy("Cowboy1", Point(0, 0)));
        YoungNinja youngNinja1("YoungNinja1", Point(1, 1));
        TrainedNinja trainedNinja1("TrainedNinja1", Point(2, 2));
        OldNinja oldNinja1("OldNinja1", Point(3, 3));
        Cowboy cowboy2("Cowboy2", Point(4, 4));

        team1.add(&youngNinja1);
        team1.add(&trainedNinja1);
        team1.add(&oldNinja1);
        team1.add(&cowboy2);

        Team team2(new Cowboy("Cowboy3", Point(10, 10)));
        YoungNinja youngNinja2("YoungNinja2", Point(11, 11));
        TrainedNinja trainedNinja2("TrainedNinja2", Point(12, 12));
        OldNinja oldNinja2("OldNinja2", Point(13, 13));
        Cowboy cowboy4("Cowboy4", Point(14, 14));

        team2.add(&youngNinja2);
        team2.add(&trainedNinja2);
        team2.add(&oldNinja2);
        team2.add(&cowboy4);

        int maxRounds = 200;
        int round = 0;

        // Simulate a series of attacks until one team is defeated or maxRounds is reached
        while (team1.stillAlive() > 0 && team2.stillAlive() > 0 && round < maxRounds) {
            team1.attack(&team2);
            team2.attack(&team1);
            round++;
        }

        // Check if one of the teams has been defeated
        bool flag = (team1.stillAlive() > 0 && team2.stillAlive() > 0);
        CHECK_FALSE(flag == true);
    }

}

TEST_CASE("Team stillAlive method") {
    Team team;

    // Add characters to the team
    team.add(new Cowboy("Cowboy 1", Point(1, 1)));
    team.add(new YoungNinja("Ninja 1", Point(2, 2)));

    CHECK(team.stillAlive() == 3);

    // Kill one character in the team
    CHECK_THROWS(team.attack(&team)); // Self-attack to simulate character death
}

TEST_CASE("Testing Point class") {
    Point p_1(0, 0);
    Point p_2(3, 4);
    CHECK(p_1.distance(p_2) == 5.0);
    CHECK(p_2.distance(p_1) == 5.0);
    CHECK(p_1.distance(p_1) == 0.0);

    Point p_3(-3, 4);
    CHECK(p_1.distance(p_3) == 5.0);
    CHECK(p_3.distance(p_1) == 5.0);

    Point p_4(-3, -4);
    CHECK(p_1.distance(p_4) == 5.0);
    CHECK(p_4.distance(p_1) == 5.0);

    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    CHECK(p1.distance(p2) == doctest::Approx(5.0).epsilon(0.01));

    Point p3 = moveTowards(p1, p2, 1.0);
    CHECK(p3.getX() == doctest::Approx(0.6).epsilon(0.01));
    CHECK(p3.getY() == doctest::Approx(0.8).epsilon(0.01));

    Point p4 = moveTowards(p1, p2, 5.0);
    CHECK(p4.getX() == doctest::Approx(3.0).epsilon(0.01));
    CHECK(p4.getY() == doctest::Approx(4.0).epsilon(0.01));

    Point p5(1.0, 1.0);
    Point p6(1.0, 2.0);
    CHECK(p5.distance(p6) == doctest::Approx(1.0).epsilon(0.01));

    Point p7 = moveTowards(p5, p6, 1.0);
    CHECK(p7.getX() == doctest::Approx(1.0).epsilon(0.01));
    CHECK(p7.getY() == doctest::Approx(2).epsilon(0.01));

    Point p8(0.0, 0.0);
    Point p9(10.0, 0.0);
    CHECK(p8.distance(p9) == doctest::Approx(10.0).epsilon(0.01));

    Point p10 = moveTowards(p8, p9, 5.0);
    CHECK(p10.getX() == doctest::Approx(5.0).epsilon(0.01));
    CHECK(p10.getY() == doctest::Approx(0.0).epsilon(0.01));

    Point p11(-3.0, -4.0);
    Point p12(3.0, 4.0);
    CHECK(p11.distance(p12) == doctest::Approx(10.0).epsilon(0.01));

    Point p13 = moveTowards(p11, p12, 5.0);
    CHECK(p13.getX() == doctest::Approx(0.0).epsilon(0.01));
    CHECK(p13.getY() == doctest::Approx(0.0).epsilon(0.01));

    Point p14(0.0, 0.0);
    Point p15(0.0, -5.0);
    CHECK(p14.distance(p15) == doctest::Approx(5.0).epsilon(0.01));

    Point p16 = moveTowards(p14, p15, 3.0);
    CHECK(p16.getX() == doctest::Approx(0.0).epsilon(0.01));
    CHECK(p16.getY() == doctest::Approx(-3.0).epsilon(0.01));

    Point p17(1.0, 1.0);
    Point p18(-1.0, 1.0);
    CHECK(p17.distance(p18) == doctest::Approx(2.0).epsilon(0.01));

    Point p19 = moveTowards(p17, p18, 0.5);
    CHECK(p19.getX() == doctest::Approx(0.5).epsilon(0.01));
    CHECK(p19.getY() == doctest::Approx(1.0).epsilon(0.01));

    Point p20(-3.0, -4.0);
    Point p21(-6.0, -8.0);
    CHECK(p20.distance(p21) == doctest::Approx(5.0).epsilon(0.01));

    Point p22 = moveTowards(p20, p21, 2.5);
    CHECK(p22.getX() == doctest::Approx(-4.5).epsilon(0.01));
    CHECK(p22.getY() == doctest::Approx(-6.0).epsilon(0.01));
}

TEST_CASE("Testing moveTowards function") {
    Point p1(0, 0);
    Point p2(10, 0);
    Point p3(0, 10);
    Point p4(10, 10);
    Point p5(-10, 0);
    Point p6(0, -10);
    Point p7(-10, -10);
    double distance = 5.0;
    moveTowards(p1, p4, distance).print();
    CHECK(moveTowards(p1, p2, distance) == Point(5, 0));
    CHECK(moveTowards(p2, p1, distance) == Point(5, 0));
    CHECK(moveTowards(p1, p3, distance) == Point(0, 5));
    CHECK(moveTowards(p1, p4, distance) == Point(3.53553, 3.53553));
    CHECK(moveTowards(p1, p5, distance) == Point(-5, 0));
    CHECK(moveTowards(p1, p6, distance) == Point(0, -5));
    CHECK(moveTowards(p1, p7, distance) == Point(-3.53553, -3.53553));


    SUBCASE("Testing moveTowards with negative distances") {
        double negativeDistance = -5.0;
        CHECK_THROWS(moveTowards(p1, p2, negativeDistance));
        CHECK_THROWS(moveTowards(p2, p1, negativeDistance));
        CHECK_THROWS(moveTowards(p1, p3, negativeDistance));
        CHECK_THROWS(moveTowards(p1, p4, negativeDistance));
        CHECK_THROWS(moveTowards(p1, p5, negativeDistance));
        CHECK_THROWS(moveTowards(p1, p6, negativeDistance));
        CHECK_THROWS(moveTowards(p1, p7, negativeDistance));
    }
}


TEST_CASE("Testing characters with different initial health") {
    Character character1(Point(0, 0), 50, "Character1");
    Character character2(Point(0, 0), 0, "Character2");
    CHECK_THROWS(Character (Point(0, 0), -10, "Character3"));
    CHECK(character1.isAlive() == true);
    CHECK(character2.isAlive() == false);
}

TEST_CASE("Testing negative hit points") {
    Character character(Point(0, 0), 100, "Character");
    CHECK_THROWS(character.hit(-10));
}

TEST_CASE("Testing Ninja move and slash methods with different distances") {
    TrainedNinja ninja("Trained Ninja", Point(0, 0));
    Character enemy(Point(0.5, 0.5), 100, "Enemy");
    SUBCASE("Within slashing range") {
        ninja.slash(&enemy);
        CHECK(enemy.print() == "Enemy (0.5,0.5), 60");
    }

    SUBCASE("Out of slashing range") {
        enemy.getLocation() = Point(100, 100);
        ninja.slash(&enemy);
        CHECK(enemy.print() == "Enemy (100,100) 100");
        CHECK(enemy.print() == "Enemy (100, 100) 100");
    }

    SUBCASE("Move towards enemy") {
        ninja.move(&enemy);
        CHECK(ninja.getLocation().getX() != 0);
        CHECK(ninja.getLocation().getY() != 0);
    }
    SUBCASE("Ninja moves towards the enemy from max double position") {
        TrainedNinja ninja("Ninja1", Point(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
        Cowboy cowboy("Cowboy1", Point(0, 0));

        double initialDistance = ninja.getLocation().distance(cowboy.getLocation());
        ninja.move(&cowboy);
        double distanceAfterMove = ninja.getLocation().distance(cowboy.getLocation());
        double tolerance = 1e-9;

        CHECK(distanceAfterMove < initialDistance); // Check that the ninja moved towards the cowboy
        CHECK(std::abs(distanceAfterMove - (initialDistance - 12)) <= tolerance); // Check that the ninja moved approximately 12 units
    }

    // Test case for shoot
    SUBCASE("Cowboy shoots another cowboy, reducing the target's hit points") {
        Cowboy shooter("Shooter", Point(0, 0));
        Cowboy target("Target", Point(10, 10));

        int initialTargetHP = target.getHitPoints();
        shooter.shoot(&target);
        int targetHPAfterShoot = target.getHitPoints();

        CHECK(targetHPAfterShoot == initialTargetHP - 10); // Check that the target's hit points have been reduced by 10
    }

    // Test case for slash
    SUBCASE("Ninja slashes another ninja when the target is within 1 meter") {
        YoungNinja attacker("Attacker", Point(0, 0));
        YoungNinja target("Target", Point(0.5, 0.5));

        int initialTargetHP = target.getHitPoints();
        attacker.slash(&target);
        int targetHPAfterSlash = target.getHitPoints();

        CHECK(targetHPAfterSlash == initialTargetHP - 40); // Check that the target's hit points have been reduced by 31
    }

    SUBCASE("Ninja fails to slash another ninja when the target is more than 1 meter away") {
        YoungNinja attacker("Attacker", Point(0, 0));
        YoungNinja target("Target", Point(1.5, 1.5));

        int initialTargetHP = target.getHitPoints();
        attacker.slash(&target);
        int targetHPAfterSlash = target.getHitPoints();

        CHECK(targetHPAfterSlash == initialTargetHP); // Check that the target's hit points have not changed
    }
}

TEST_CASE("Testing Cowboy reload method") {
    Cowboy c("Cowboy", Point(0, 0));
    for (int i = 0; i < 6; ++i) {
        c.shoot(nullptr);
    }
    CHECK(c.hasboolets() == false);
    c.reload();
    CHECK(c.hasboolets() == true);
    Point cowboyPosition(5, 5);

    Cowboy cowboy("John", cowboyPosition);
    CHECK(cowboy.getName() == "John");
    CHECK(cowboy.getLocation() == cowboyPosition);
    CHECK(cowboy.isAlive() == true);
    CHECK(cowboy.hasboolets() == true);
    CHECK(cowboy.getHitPoints() == 110);

    Point enemyPosition(7, 7);
    Ninja enemy("NinjaEnemy", 100, enemyPosition, 10);

    // Test shooting
    cowboy.shoot(&enemy);
    CHECK(enemy.getHitPoints() == 90);
    CHECK(cowboy.hasboolets() == true);

    // Test reloading
    for (int i = 0; i < 5; i++) {
        cowboy.shoot(&enemy);
    }
    CHECK(cowboy.hasboolets() == false);
    cowboy.reload();
    CHECK(cowboy.hasboolets() == true);

    // Test hitting
    cowboy.hit(60);
    CHECK(cowboy.getHitPoints() == 50);
    CHECK(cowboy.isAlive() == true);

    cowboy.hit(50);
    CHECK(cowboy.getHitPoints() == 0);
    CHECK(cowboy.isAlive() == false);
}

TEST_CASE("Testing Team stillAlive method") {
    Cowboy leader("Leader", Point(0, 0));
    Team team(&leader);
    team.add(new TrainedNinja("Trained Ninja", Point(0, 0)));
    team.add(new YoungNinja("Young Ninja", Point(0, 0)));
    CHECK(team.stillAlive() == 3);
    leader.hit(110);
    CHECK(team.stillAlive() == 2);
}

TEST_CASE("Testing Characters") {
    Point p1(0, 0);
    Cowboy c1("Cowboy1", p1);
    TrainedNinja n1("TrainedNinja1", p1);
    YoungNinja n2("YoungNinja1", p1);
    OldNinja n3("OldNinja1", p1);

    SUBCASE("Testing Cowboy hit method") {
        CHECK(c1.getHitPoints() == 100);
        c1.hit(10);
        CHECK(c1.getHitPoints() == 90);
        c1.hit(100);
        CHECK(c1.getHitPoints() <= 0);
        CHECK(!c1.isAlive());
    }

    SUBCASE("Testing TrainedNinja hit method") {
        CHECK(n1.getHitPoints() == 100);
        n1.hit(10);
        CHECK(n1.getHitPoints() == 90);
        n1.hit(100);
        CHECK(n1.getHitPoints() <= 0);
        CHECK(!n1.isAlive());
    }

    SUBCASE("Testing YoungNinja hit method") {
        CHECK(n2.getHitPoints() == 100);
        n2.hit(10);
        CHECK(n2.getHitPoints() == 90);
        n2.hit(100);
        CHECK(n2.getHitPoints() <= 0);
        CHECK(!n2.isAlive());
    }

    SUBCASE("Testing OldNinja hit method") {
        CHECK(n3.getHitPoints() == 100);
        n3.hit(10);
        CHECK(n3.getHitPoints() == 90);
        n3.hit(100);
        CHECK(n3.getHitPoints() <= 0);
        CHECK(!n3.isAlive());
    }
}

TEST_CASE("Testing Characters and Point class - Extreme Edge Cases (Overflow, Limits)") {
    double max_double = std::numeric_limits<double>::max();

    Point p1(max_double, max_double);
    Point p2(max_double, -max_double);
    Point p3(-max_double, max_double);
    Point p4(-max_double, -max_double);

    Cowboy c1("Cowboy1", p1);
    TrainedNinja n1("TrainedNinja1", p2);
    YoungNinja n2("YoungNinja1", p3);
    OldNinja n3("OldNinja1", p4);

    SUBCASE("Testing extreme distance calculations with overflow checks") {
        CHECK_FALSE(p1.distance(p2) == max_double);
        CHECK_FALSE(p1.distance(p3) == max_double);
        CHECK_FALSE(p1.distance(p4) == max_double);
    }

    SUBCASE("Testing character names with extreme coordinates") {
        CHECK_THROWS(Cowboy("Cowboy2", Point(max_double - 1, max_double)));
        CHECK_THROWS(TrainedNinja("TrainedNinja2", Point(max_double, max_double + 1)));
        CHECK_THROWS(YoungNinja("YoungNinja2", Point(-max_double, -max_double - 1)));
        CHECK_THROWS(OldNinja("OldNinja2", Point(-max_double - 1, -max_double)));
    }

    SUBCASE("Testing extreme coordinate values") {
        CHECK_THROWS(Point(max_double + 1, 0));
        CHECK_THROWS(Point(0, max_double + 1));
        CHECK_THROWS(Point(max_double + 1, max_double + 1));
    }
}

TEST_CASE("Points with max values") {
    double max_double = std::numeric_limits<double>::max();
    double min_double = std::numeric_limits<double>::min();

    CHECK_NOTHROW(Point p1(max_double, max_double));
    CHECK_NOTHROW(Point p2(-max_double, max_double));
    CHECK_NOTHROW(Point p3(min_double, min_double));
    CHECK_NOTHROW(Point p4(min_double, -min_double));
}

TEST_CASE("Testing attack and move methods with different distances") {
    Cowboy cowboy1("Cowboy1", Point(0, 0));
    TrainedNinja ninja1("Ninja1", Point(5, 5));
    Character enemy1(Point(5, 5), 100, "Enemy1");
    SUBCASE("Cowboy1 within shooting range") {
        cowboy1.shoot(&enemy1);
        CHECK(enemy1.print() == "Enemy1 (5,5) 90");
    }

    SUBCASE("Ninja1 within slashing range") {
        ninja1.slash(&enemy1);
        CHECK(enemy1.print() == "Enemy1 (5,5) 50");
    }

    SUBCASE("Ninja1 out of slashing range") {
        ninja1.getLocation() = Point(100, 100);
        ninja1.slash(&enemy1);
        CHECK(enemy1.print() == "Enemy1 (5,5) 50");
    }

    SUBCASE("Move Ninja1 towards enemy1") {
        ninja1.move(&enemy1);
        CHECK(ninja1.getLocation().getX() != 5);
        CHECK(ninja1.getLocation().getX() != 5);
    }
}

TEST_CASE("Testing multiple character interactions") {
    Point p1(0, 0);
    Cowboy c1("Cowboy1", p1);
    TrainedNinja n1("TrainedNinja1", p1);
    YoungNinja n2("YoungNinja1", p1);
    OldNinja n3("OldNinja1", p1);
    Character enemy1(Point(10, 10), 100, "Enemy1");
    SUBCASE("All characters attacking enemy1") {
        c1.shoot(&enemy1);
        n1.slash(&enemy1);
        n2.slash(&enemy1);
        n3.slash(&enemy1);
        CHECK(enemy1.print() == "(Enemy1) (10,10)");
    }

    SUBCASE("ninjas moving towards enemy1") {
        n1.move(&enemy1);
        n2.move(&enemy1);
        n3.move(&enemy1);
        CHECK(n1.getLocation().getX() != 0);
        CHECK(n1.getLocation().getY() != 0);
        CHECK(n2.getLocation().getX() != 0);
        CHECK(n2.getLocation().getY() != 0);
        CHECK(n3.getLocation().getX() != 0);
        CHECK(n3.getLocation().getY() != 0);
    }
}

TEST_CASE("Testing character health with hit_pts overflow") {
    Character character(Point(0, 0), std::numeric_limits<int>::max(), "Character");
    character.hit(std::numeric_limits<int>::max() - 50);
    CHECK(character.isAlive() == true);
    CHECK(character.getHitPoints() > 0);
    CHECK(character.getHitPoints() <= std::numeric_limits<int>::max());
}

TEST_CASE("Testing Ninja class")
{
    Point location(1.0, 2.0);
    Ninja n("Mike", 10, location, 5);

    SUBCASE("Testing isAlive method") {
        CHECK(n.isAlive() == true);
        n.hit(10);
        CHECK(n.isAlive() == false);
    }

    SUBCASE("Testing slash method") {
        Point location2(1.0, 3.0);
        Ninja n2("John", 10, location2, 5);
        n.slash(&n2);
        CHECK(n2.isAlive() == false);
        Point location3(5.0, 6.0);
        Ninja n3("Mike", 500, location3, 5);
        n.slash(&n3);
        CHECK(n3.isAlive() == true);
    }
}

TEST_CASE("Testing Team class")
{
    Point location1(1.0, 2.0);
    Point location2(3.0, 4.0);
    Point location3(5.0, 6.0);
    Cowboy c1("John", location1);
    Ninja n1("Mike", 0, location2, 5);
    Cowboy c2("Mike", location3);

    Team team1(&c1);
    team1.add(&n1);
    team1.add(&c2);

    SUBCASE("Testing adding same character") {
        CHECK(team1.stillAlive() > 0);
        Cowboy c3("Dave", Point(0.0, 0.0));
        for (int i = 0; i < 1000; i++) {
            team1.add(&c3);
        }
        CHECK(team1.stillAlive() == 4);
    }

}

TEST_CASE("Testing Team2 class")
{
    Point location1(1.0, 2.0);
    Point location2(3.0, 4.0);
    Point location3(5.0, 6.0);
    Cowboy c1("John", location1);
    Ninja n1("Mike", 0, location2, 5);
    Cowboy c2("Mike", location3);

    Team2 team1(&c1);
    team1.add(&n1);
    team1.add(&c2);

    SUBCASE("Testing attack method") {
        Point location4(1.0, 3.0);
        Point location5(2.0, 3.0);
        Cowboy c3("Dave", location4);
        Cowboy c4("Alex", location5);
        Team2 team2(&c3);
        team2.add(&c4);
        while(team2.stillAlive()>0)
            team1.attack(&team2);

        CHECK(n1.isAlive() == false);
        CHECK(c3.isAlive() == false);
        CHECK(c4.isAlive() == false);
    }
    Point pt;

    SUBCASE("Testing destructor") {
        Point pt;
        Cowboy *c1 = new Cowboy("C1", pt);
        Cowboy *c2 = new Cowboy("C2",pt);
        Cowboy *c3 = new Cowboy("C3",pt);
        {
            Team2 team(c1);
            team.add(c2);
            team.add(c3);
        }
        //trying to access freed pointer
        CHECK_THROWS(c1->isAlive());
        CHECK_THROWS(c2->isAlive());
        CHECK_THROWS(c3->isAlive());
    }
}

TEST_CASE("Testing Team class")
{
    Point pt;
    SUBCASE("Testing SmartTeam destructor") {
        Cowboy *c1 = new Cowboy("C1", pt);
        Cowboy *c2 = new Cowboy("C2",pt);
        Cowboy *c3 = new Cowboy("C3",pt);
        {
            SmartTeam team3(c1);
            team3.add(c2);
            team3.add(c3);
        }
        CHECK_THROWS(c1->isAlive());
        CHECK_THROWS(c2->isAlive());
        CHECK_THROWS(c3->isAlive());
    }
}

TEST_CASE("Edge cases and complex tests") {
    Point point1(0, 0);
    Point point2(3, 4);
    Point point3(-3, -4);
    Point point4(1, 1);
    CHECK(point1.distance(point2) == 5);
    CHECK(point1.distance(point3) == 5);
    CHECK(point1.distance(point4) == doctest::Approx(1.414));

    // Test case 2: Move towards
    Point source(0, 0);
    Point dest(5, 5);
    double distance = 2;
    Point newPoint = moveTowards(source, dest, distance);
    CHECK(newPoint.getX() == 2);
    CHECK(newPoint.getY() == 2);
}

TEST_CASE("More edge cases and complex tests") {
    // Cowboys shooting
    Point pt(0, 0);
    Cowboy cowboy1("Cowboy1", pt);
    Cowboy cowboy2("Cowboy2", pt);

    // Initial hit points
    CHECK(cowboy1.getHitPoints() == 110);
    CHECK(cowboy2.getHitPoints() == 110);

    // Cowboy1 shoots Cowboy2
    cowboy1.shoot(&cowboy2);
    CHECK(cowboy1.hasboolets() == true);

    //  Ninjas moving towards the enemy and slashing
    YoungNinja youngNinja("YoungNinja", pt);
    TrainedNinja trainedNinja("TrainedNinja", pt);
    OldNinja oldNinja("OldNinja", pt);
    Cowboy cowboy3("Cowboy3", pt);

    youngNinja.move(&cowboy3);
    trainedNinja.move(&cowboy3);
    oldNinja.move(&cowboy3);

    youngNinja.slash(&cowboy3);
    trainedNinja.slash(&cowboy3);
    oldNinja.slash(&cowboy3);

    CHECK(cowboy3.isAlive() == false);
}

TEST_CASE("Testing print functionality") {
    Point cowboyPoint1(0, 0);
    Cowboy cowboy1("Cowboy1", cowboyPoint1);
    CHECK(cowboy1.print() == "C Cowboy1 (0,0) 110");

    Point youngNinjaPoint(0, 0);
    YoungNinja youngNinja("YoungNinja", youngNinjaPoint);
    CHECK(youngNinja.print() == "N YoungNinja (0,0) 100");

    Point deadNinjaPoint(1, 1);
    YoungNinja deadNinja("DeadNinja", deadNinjaPoint);
    deadNinja.hit(100);
    CHECK(deadNinja.print() == "N (DeadNinja) (1,1)");
    Point deadCowboyPoint(2, 2);
    Cowboy deadCowboy("DeadCowboy", deadCowboyPoint);
    deadCowboy.hit(110);
    CHECK(deadCowboy.print() == "C (DeadCowboy) (2,2)");

    Point characterPoint(3, 3);
    Character character(characterPoint, 100, "Character");
    CHECK(character.print() == "Character (3,3) 100");

    Point deadCharPoint(4, 4);
    Character deadChar(deadCharPoint, 0, "deadCharacter");
    CHECK(deadChar.print() == "(deadCharacter) (4,4)");
}

TEST_CASE("Testing shoot, slash, and move functionality") {
    //Cowboy shooting an enemy
    Point cowboyPoint1(0, 0);
    Cowboy cowboy1("Cowboy1", cowboyPoint1);
    Point ninjaPoint1(0, 0.9);
    YoungNinja youngNinja1("YoungNinja1", ninjaPoint1);

    cowboy1.shoot(&youngNinja1);
    CHECK(youngNinja1.getHitPoints() == 90);

    for (int i = 0; i < 5; i++) {
        cowboy1.shoot(&youngNinja1);
    }
    CHECK(youngNinja1.getHitPoints() == 30);
    CHECK(cowboy1.hasboolets() == false);
    cowboy1.reload();
    CHECK(cowboy1.hasboolets() == true);
    cowboy1.shoot(&youngNinja1);
    CHECK(youngNinja1.getHitPoints() == 20);
    youngNinja1.slash(&cowboy1);
    CHECK(cowboy1.getHitPoints() == 70);
    youngNinja1.slash(&cowboy1);
    CHECK(cowboy1.getHitPoints() == 30);
    youngNinja1.slash(&cowboy1);
    CHECK(!cowboy1.isAlive());

    CHECK_THROWS(cowboy1.shoot(&youngNinja1));

    Point ninjaPoint2(1, 1);
    YoungNinja youngNinja2("YoungNinja2", ninjaPoint2);
    Point cowboyPoint2(1, 2);
    Cowboy cowboy2("Cowboy2", cowboyPoint2);

    youngNinja2.slash(&cowboy2);
    CHECK(cowboy2.getHitPoints() == 70);

    Point ninjaPoint3(1, 1);
    YoungNinja youngNinja3("YoungNinja3", ninjaPoint3);
    Point cowboyPoint3(3, 3);
    Cowboy cowboy3("Cowboy3", cowboyPoint3);

    youngNinja3.slash(&cowboy3);
    CHECK(cowboy3.getHitPoints() == 110);

    Point ninjaPoint4(0, 0);
    YoungNinja youngNinja4("YoungNinja4", ninjaPoint4);
    OldNinja oldNinja("Ishimoto", Point(14, 0));

    youngNinja4.move(&oldNinja);
    CHECK(youngNinja4.getLocation().getX() == 14);
    CHECK(youngNinja4.getLocation().getY() == 0);

    Point ninjaPoint5(0, 0);
    YoungNinja youngNinja5("YoungNinja5", ninjaPoint5);
    TrainedNinja trainedNinja("Hashimoto", Point(10, 0));

    youngNinja5.move(&trainedNinja);
    CHECK(youngNinja5.getLocation().getX() == 10);
    CHECK(youngNinja5.getLocation().getY() == 0);
}

TEST_CASE("Point distance and moveTowards") {
    Point p1(0, 0);
    Point p2(3, 4);

    CHECK(p1.distance(p2) == 5.0);

    Point p3 = moveTowards(p1, p2, 2);
    CHECK(p3.distance(p1) == 2.0);
    CHECK(p3.distance(p2) == 3.0);
}

TEST_CASE("Character interactions") {
    Cowboy cowboy("Cowboy 1", Point(1, 1));
    YoungNinja ninja("Ninja 1", Point(2, 2));

    double initialDistance = cowboy.distance(&ninja);
    CHECK(initialDistance == Approx(sqrt(2)));

    cowboy.shoot(&ninja);
    CHECK(ninja.getHitPoints() == 90);

    ninja.move(&cowboy);
    double newDistance = cowboy.distance(&ninja);
    CHECK(newDistance < initialDistance);
}
TEST_CASE("Test cases for add method and stillAlive") {
    SUBCASE("Add a large number of characters to a team and check the number of characters alive") {
        Team team(new Cowboy("Cowboy1", Point(0, 0)));
        for (int i = 2; i <= 10; i++) {
            team.add(new Cowboy("Cowboy" + std::to_string(i), Point(i, i)));
        }
        for (int i = 1; i <= 10; i++) {
            team.add(new YoungNinja("YoungNinja" + std::to_string(i), Point(10 + i, 10 + i)));
        }

        for (int i = 1; i <= 10; i++) {
            team.add(new TrainedNinja("TrainedNinja" + std::to_string(i), Point(20 + i, 20 + i)));
        }
        for (int i = 1; i <= 10; i++) {
            team.add(new OldNinja("OldNinja" + std::to_string(i), Point(30 + i, 30 + i)));
        }
        CHECK(team.stillAlive() == 40);
    }
}
TEST_CASE("Adding too many characters to a team") {
    Team team1(new Cowboy("Cowboy1", Point(10, 10)));

    // Add 10 characters to team1
    for (int i = 0; i < 9; i++) {
        team1.add(new OldNinja("OldNinja", Point(11+i, 11+i)));
    }

    // Try to add an 11th character to team1, should throw an exception
    CHECK_THROWS_AS(team1.add(new YoungNinja("YoungNinja", Point(21, 21))), std::runtime_error);
}

TEST_CASE("Trying to perform action for dead characters")
{
    Cowboy c1("Cowboy1",Point(17,17));
    c1.hit(110);
    YoungNinja n1("YoungNinja1",Point(17,17));
    n1.hit(100);
    TrainedNinja n2("TrainedNinja2",Point(17,17));
    n2.hit(120);
    OldNinja n3("OldNinja3",Point(17,17));
    n3.hit(150);

    Cowboy dummy("Dummy",Point(421,421));

    CHECK_THROWS(c1.shoot(&dummy));
    CHECK_THROWS(n1.move(&dummy));
    CHECK_THROWS(n1.slash(&dummy));
    CHECK_THROWS(n2.move(&dummy));
    CHECK_THROWS(n2.slash(&dummy));
    CHECK_THROWS(n3.move(&dummy));
    CHECK_THROWS(n3.slash(&dummy));
}
TEST_CASE("Battle scenario checking all attack rules") {
    // Setting up Characters
    Point initialPoint1(0, 0);
    Cowboy cowboy1("Cowboy1", initialPoint1);

    Point initialPoint2(10, 0);
    Cowboy cowboy2("Cowboy2", initialPoint2);

    Point initialPoint3(20, 0);
    YoungNinja youngNinja1("YoungNinja1", initialPoint3);

    Point initialPoint4(30, 0);
    TrainedNinja trainedNinja1("TrainedNinja1", initialPoint4);

    Point initialPoint5(40, 0);
    OldNinja oldNinja1("OldNinja1", initialPoint5);

    // Setting up teams
    Team cowboysTeam(&cowboy1);
    cowboysTeam.add(&cowboy2);

    Team ninjasTeam(&youngNinja1);
    ninjasTeam.add(&trainedNinja1);
    ninjasTeam.add(&oldNinja1);

    // Battle simulation
    // Cowboys attack
    for (int i = 0; i < 6; ++i) {
        cowboysTeam.attack(&ninjasTeam);  // Deal 20 damage every attack to the closest (Trained Ninja)
    }
    REQUIRE(cowboy1.hasboolets()==false);
    REQUIRE(cowboy2.hasboolets()==false);

    // Check if the TrainedNinja1 is dead as it was the closest to the Cowboys
    REQUIRE(trainedNinja1.isAlive() == false);

    ninjasTeam.attack(&cowboysTeam);

    // Check if both of ninjas moved towards cowboy2 since its closest to cowboy1(leader)
    REQUIRE(youngNinja1.getLocation().distance(cowboy2.getLocation()) < 10.0);
    REQUIRE(oldNinja1.getLocation().distance(cowboy2.getLocation()) < 30.0);

    while(cowboy2.isAlive())
        ninjasTeam.attack(&cowboysTeam);

    for (int i = 0; i < 15; ++i) { //hit the old ninja for all of its health
        cowboysTeam.attack(&ninjasTeam);
    }
    REQUIRE(oldNinja1.isAlive() == false);

    for (int i = 0; i < 4; ++i) {
        ninjasTeam.attack(&cowboysTeam);
    }
    REQUIRE(cowboy1.isAlive() == false);
    // Check if the Cowboy1 is dead as it was the only cowboy left
    // Check if the attack ends as there are no living members in the cowboys team
    REQUIRE(ninjasTeam.stillAlive() == 1);
    REQUIRE(cowboysTeam.stillAlive() == 0);
}

TEST_CASE("Hitting a character with max double")
{
    double max_double = std::numeric_limits<double>::max();
    Cowboy c("Cowboy",Point(0,0));
    c.hit(110);
    c.hit(max_double);
    CHECK_THROWS_AS(c.hit(1),std::overflow_error);
}
