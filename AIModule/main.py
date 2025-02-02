# main.py

from Character import Player, NPC

def main():
    player = Player("Player", {"building": 10, "crafting": 8}, 15, 12)
    npc = NPC("NPC", {"building": 5, "crafting": 7}, 10, 10)

    print(f"Cooperation level between {player.name} and {npc.name}: {player.calculate_cooperation_level(npc)}")

    player.perform_action("building")
    npc.perform_action("crafting")

    player.gain_experience("building")
    npc.gain_experience("crafting")

    player.improve_skills()
    npc.improve_skills()

    print(f"{player.name}'s skills: {player.skills}")
    print(f"{npc.name}'s skills: {npc.skills}")

if __name__ == "__main__":
    main()