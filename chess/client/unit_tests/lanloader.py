import chess.pgn

pgn = open("axvesik_vs_Missile2019_2023.05.22.pgn")

game = chess.pgn.read_game(pgn)

board = game.board()
for move in game.mainline_moves():
	print(move)
