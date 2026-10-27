# Content locked by the server

A server can release its content step by step, e.g. starting with the maps and
features of an early season and unlocking the later ones over time (the
*content stages* of Torvik MU's OpenMU server). It tells the client which
content is still locked when a character enters the game, and the client hides
the user interface of that content:

- **Locked maps** aren't listed in the move window (M), so they can't be chosen
  there. An entry is hidden when the map of the gate it warps to is locked.
- **Gens:** the window menu has no gens row (it shows five rows), the B key
  doesn't open the gens window and the chat bar has no gens chat button. In the
  legacy theme the button's art is part of the chat bar's background, so only
  its function goes away.
- **Cash shop:** the shop buttons of the HUD are hidden and the X key doesn't
  open the shop.

The server still checks everything on its side: hiding the user interface only
spares the player options that can't work.

Without the message nothing is locked: servers which don't send it, e.g. other
OpenMU servers, get the full user interface. The client forgets the locked
content when the character list is shown, and the server sends it again when the
next character enters the game, so a release of content takes effect with the
next character selection.

## The message

The locked content message is a custom message of Torvik MU (C2, head code
`FA`). Clients which don't know it ignore it.

| Bytes | Content |
|---|---|
| 0-3 | C2 header: `C2`, the size (big endian), `FA` |
| 4 | Flags: bit 0 = gens locked, bit 1 = cash shop locked |
| 5 | Count of locked maps |
| 6- | The numbers of the locked maps, 2 bytes each, little endian |
