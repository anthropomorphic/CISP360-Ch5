#include <iostream>
#include <random>
using namespace std;

///
/// `answer_t` is the return type used by the four do_math functions.
/// It holds both the correct answer, and the user's given answer.
///
typedef struct {
    unsigned given;
    unsigned correct;
} answer_t;

/// mt19937 is a random number generator (mersenne twister engine)
/// from here on referred to as RNG.
typedef mt19937 rng_t;

unsigned get_number_in_range(unsigned, unsigned, rng_t);
string get_snarky_response(bool, rng_t);
answer_t do_addition(rng_t);
answer_t do_subtraction(rng_t);
answer_t do_multiplication(rng_t);
answer_t do_division(rng_t);

int main()
{
    // Random number generator
    random_device rd;
    rng_t rng(rd());

    answer_t answer;

    answer = do_addition(rng);

    if (answer.given == answer.correct)
    {
        string response = get_snarky_response(true, rng);
        cout << endl
             << response << endl;
    }
    else
    {
        string response = get_snarky_response(false, rng);
        cout << response << endl
             << endl
             << "The answer is " << answer.correct << endl;
    }
}

///
/// Provides the user with an addition problem to solve.
/// All numbers used will be 3 digits (including the answer).
///
/// Returns `answer_t`, which holds both the correct answer,
/// and the answer provided by the user.
///
answer_t do_addition(rng_t rng)
{
    answer_t answer;
    answer.correct = get_number_in_range(200, 999, rng);
    unsigned addend = get_number_in_range(100, answer.correct - 100, rng);
    unsigned augend = answer.correct - addend;

    cout << endl << endl
         << "   " << addend << endl
         << " + " << augend << endl
         << "------" << endl;

    cout << "   ";
    cin >> answer.given;

    return answer;
}

///
/// Just a simple utility to return a random number from
/// `range_start` to `range_end` (inclusive).
///
unsigned get_number_in_range(unsigned range_start, unsigned range_end, rng_t rng)
{
    uniform_int_distribution<> distribution(range_start, range_end);
    return distribution(rng);
}

///
/// Returns a random snarky response to the caller.
/// If `answer_correct` is true, it will return a "correct answer" response.
/// If `answer_correct` is false, it will return an "incorrect answer" response.
///
string get_snarky_response(bool answer_correct, rng_t rng)
{
    // I want to generate a random snarky response, out of a pool
    // of snarky responses.
    // I need a random number to select which response I will use.
    uniform_int_distribution<> snarky_response_dist(0, 3);
    size_t snarky_response_index = snarky_response_dist(rng);

    // Here are my pools of snarky responses
    const string snarky_positive_response_pool[] = {
        "You're a mathematical genius.",
        "Good job. We're all very impressed.",
        "Arithmetic ain't got nothin on you.",
        "Oh bravo. You're an inspiration to us all."
    };
    const string snarky_negative_response_pool[] = {
        "Trump says: WRONG!!!",
        "You need help.",
        "You forgot to carry the 1, genius.",
        "Oh COME ON..."
    };

    if (answer_correct)
    {
        return snarky_positive_response_pool[snarky_response_index];
    }
    else
    {
        return snarky_negative_response_pool[snarky_response_index];
    }
}
