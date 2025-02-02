# character.py

import random

# キャラクター定義用ベースクラス
class Character:
    def __init__(self, name, skills, strength, intelligence):
        self.name = name
        self.skills = skills
        self.strength = strength
        self.intelligence = intelligence
        self.cooperation_level = 0
        self.skill_level = 0

    def calculate_cooperation_level(self, other):
        self.cooperation_level = (self.intelligence + other.intelligence) / 2
        return self.cooperation_level

    def perform_action(self, action):
        if action in self.skills:
            success_chance = self.strength + self.intelligence + self.skills[action]
            if random.randint(0, 100) < success_chance:
                print(f"{self.name} successfully performed {action}!")
                return True
            else:
                print(f"{self.name} failed to perform {action}.")
                return False
        else:
            print(f"{self.name} does not have the skill to perform {action}.")
            return False

    def gain_experience(self, skill):
        if skill in self.skills:
            self.skills[skill] += 1
            print(f"{self.name} gained experience in {skill}!")
        else:
            self.skills[skill] = 1
            print(f"{self.name} learned a new skill: {skill}!")

    def improve_skills(self):
        self.skill_level = (self.strength + self.intelligence) / 2
        for skill in self.skills:
            self.skills[skill] += self.skill_level

# プレイヤー定義用クラス
class Player(Character):
    def __init__(self, name, skills, strength, intelligence):
        super().__init__(name, skills, strength, intelligence)

# NPC定義用クラス
class NPC(Character):
    def __init__(self, name, skills, strength, intelligence):
        super().__init__(name, skills, strength, intelligence)