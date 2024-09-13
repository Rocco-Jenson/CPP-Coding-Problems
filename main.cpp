#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

// For Debugging
using std::cout;
using std::endl;

template <typename FN_ARG>
class FunctionControl {
private:
  FN_ARG fn_result;
  FN_ARG fn_argument;
  const char* fn_name;

public:
  FunctionControl(FN_ARG res, FN_ARG arg, const char* name) : fn_result(res), fn_argument(arg), fn_name(name) {
  if (fn_result != fn_argument) {
      std::cout << fn_name << " Err" << std::endl;
    } else {
      std::cout << fn_name << " Passed" << std::endl;
    }
  }
};

/*
------------------------------------------------------------------------
FUNCTION DECLARATIONS HERE
*/
int return_sum(int x, int y);
bool isSafeBridge(const std::string input);
int combinations(const std::vector<int>& input);
std::string reverse_coding(const std::string input);
std::string caesarCipher(const std::string input_str, const unsigned int shift);
std::string spaceMessage(const std::string input_str);

/*
------------------------------------------------------------------------
INT MAIN HERE
*/
int main() {
  FunctionControl<int> fn1(return_sum(3, 2), (int)5, "return_sum");
  FunctionControl<bool> fn2(isSafeBridge(std::string{"####"}), (bool)true, "isSafeBridge");
  FunctionControl<int> fn3(combinations(std::vector<int>{3, 7, 4}), (int)84, "combinations");
  FunctionControl<std::string> fn4(reverse_coding(std::string{"T4S2V2"}), (std::string)"TTTTSSVV", "reverse_coding");
  FunctionControl<std::string> fn5(caesarCipher(std::string{"A friend in need is a friend indeed"}, 20), (std::string)"U zlcyhx ch hyyx cm u zlcyhx chxyyx", "ceaserCipher");
  FunctionControl<std::string> fn6(spaceMessage("IF[2E]LG[5O]D"), (std::string)"IFEELGOOOOOD", "spaceMessage");

  return 0;
}

/*
------------------------------------------------------------------------
PROBLEM FUNCTIONS AND DEFINITIONS HERE
*/

// VERY EASY PROBLEM:
// Return the Sum of Two Numbers
// addition(3, 2) ➞ 5
int return_sum(int x, int y) {
  return x + y;
}

// EASY PROBLEM:
// Create a function which validates whether a bridge
// is safe to walk on (i.e. has no gaps in it to fall
// through).
// isSafeBridge("####") ➞ true
bool isSafeBridge(const std::string input) {
  for (unsigned short i{}; i <= input.length(); i++) {
    if (input[i] == ' ') {
      return false;
    } else {
      continue;
    }
  }

  return true;
}

// MEDIUM PROBLEM:
// Create a function that takes a variable number of arguments,
// each argument representing the number of items in a group.
// The function should return the number of permutations (combinations)
// of choices you would have if you selected one item from each group.
// combinations([3, 7, 4]) ➞ 84
int combinations(const std::vector<int>& input) {
    int ret_val{1};

    for (unsigned long long i{}; i < input.size(); i++) {
        if (input[i] != 0) {
            ret_val *= input[i];
        } else {
            continue;
        }
    }

    return ret_val;
}

// HARD PROBLEM:
// This is a reverse coding challenge. Normally you're given explicit directions
// with how to create a function. Here, you must generate your own function to satisfy
// the relationship between the inputs and outputs.
// Your task is to create a function that, when fed the inputs below,
// produce the sample outputs shown.
// "T4S2V2" ➞ "TTTTSSVV"
std::string reverse_coding(const std::string input) {
    std::string ret_str{};
   
    char last_char_state{'\0'};
    int last_int_state{-1};

    for (char in_char : input) {
        if (std::isalpha(in_char)) {
            last_char_state = in_char;
        } else {
            last_int_state = in_char - '0';
        }

        if (last_char_state == '\0' || last_int_state == -1) {
            continue;
        }

        for (int i{}; i < last_int_state; i++) {
            ret_str.push_back(last_char_state);
        }

        last_char_state = '\0';
        last_int_state = -1;
    }
   
    return ret_str;
}

// VERY HARD PROBLEM:
// Julius Caesar protected his confidential information by encrypting it using a cipher.
// Caesar's cipher (check Resources tab for more info) shifts each letter by a number of letters.
// If the shift takes you past the end of the alphabet, just rotate back to the front of the alphabet.
// In the case of a rotation by 3, w, x, y and z would map to z, a, b and c.
// Create a function that takes a string s (text to be encrypted) and an integer k (the rotation factor).
// It should return an encrypted string.
// caesarCipher("A friend in need is a friend indeed", 20) ➞ "U zlcyhx ch hyyx cm u zlcyhx chxyyx"
std::string caesarCipher(const std::string input_str, const unsigned int shift) {
  std::string ret_str{};

  unsigned short last_int_state{};
  char last_char_state{};

  std::vector<char> alpha_high;
  std::vector<char> alpha_low;

  // Initialize Vectors With Alphabet
  for (char c = 'A'; c <= 'Z'; c++) {
    alpha_high.push_back(c);
  }

  for (char c = 'a'; c <= 'z'; c++) {
    alpha_low.push_back(c);
  }

  // Find Vector Char Index And Add Shift Through Reference
  auto shift_fill_str = [&](std::vector<char> alpha_vec) -> void {
    for (char alpha_char : alpha_vec) {
        if (alpha_char == last_char_state) {
          unsigned int position = std::distance(alpha_vec.begin(), std::find(alpha_vec.begin(), alpha_vec.end(), alpha_char));

          last_int_state = position + shift;

          while (last_int_state > 25) {
            // Wrap Alphabet
            last_int_state -= 26;
          }

          ret_str.push_back(alpha_vec[last_int_state]);
        }

        last_int_state = 0;
      }
  };

  for (char in_char : input_str) {
    last_char_state = in_char;

    if (std::isupper(in_char)) {
      shift_fill_str(alpha_high);
    } else if (std::islower(in_char)) {
      shift_fill_str(alpha_low);
    } else {
      ret_str.push_back(in_char);
    }
  }

  return ret_str;
}

// EXPERT PROBLEM:
// You have received an encrypted message from space. Your task is to decrypt the message with the following simple rules:
// Message string will consist of capital letters, numbers, and brackets only.
// When there's a block of code inside the brackets, such as [10AB], it means you need to repeat the letters AB for 10 times.
// Message can be embedded in multiple layers of blocks.
// Final decrypted message will only consist of capital letters.
// Create a function that takes encrypted message str and returns the decrypted message.
// spaceMessage("IF[2E]LG[5O]D") ➞ "IFEELGOOOOOD"
std::string spaceMessage(const std::string input_str) {
  std::string ret_str{};

  short last_int_state{-1};
  char last_char_state{'\0'};
  bool char_state{};

  std::vector<char> bracket_chars{};

  for (char in_char : input_str) {
    if (in_char == '[') {
      char_state = true;
    } else if (in_char == ']') {
      char_state = false;
    } else if (char_state && in_char != '[') {
      bracket_chars.push_back(in_char);
    }

    if (std::isalpha(in_char)) {
      ret_str.push_back(in_char);
    }
  }

  for (char in_char : bracket_chars) {
    std::string insert_str{};

    if (std::isdigit(in_char)) {
      last_int_state = in_char - '0';
    } else {
      last_char_state = in_char;
    }

    if (last_char_state == '\0' || last_int_state == -1) {
      continue;
    }

    for (unsigned short i{}; i < last_int_state - 1; i++) {
      insert_str.push_back(last_char_state);
    }

    ret_str.insert(ret_str.find(last_char_state), insert_str);

    last_char_state = '\0';
    last_int_state = -1;
  }

  return ret_str;
}
