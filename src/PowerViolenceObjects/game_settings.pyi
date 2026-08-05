class _PV_str_names_array:  ##
    def __len__(self): pass  ##
    def __getitem__(self, key): pass  ##
    def __setitem__(self, key, value): pass  ##
    def __delitem__(self, key): pass ##

class GameSettings:
    numbers_of_players: int
    names_of_players: _PV_str_names_array
