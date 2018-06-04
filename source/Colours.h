#ifndef SQUAREPINE_COLOURS_H
#define SQUAREPINE_COLOURS_H

/** Contains a set of predefined named colours (mostly standard HTML colours)

    @see Colour
*/
class Colours
{
public:
    static const Colour

    //==============================================================================
    transparentBlack,   /**< ARGB = 0x00000000 */
    transparentWhite,   /**< ARGB = 0x00ffffff */

    //==============================================================================
    black,              /**< ARGB = 0xff000000 */
    white,              /**< ARGB = 0xffffffff */
    blue,               /**< ARGB = 0xff0000ff */
    grey,               /**< ARGB = 0xff808080 */
    green,              /**< ARGB = 0xff008000 */
    red,                /**< ARGB = 0xffff0000 */
    yellow,             /**< ARGB = 0xffffff00 */

    //==============================================================================
    aliceblue,         antiquewhite,       aqua,                   aquamarine,
    azure,             beige,              bisque,                 blanchedalmond,
    blueviolet,        brown,              burlywood,              cadetblue,
    chartreuse,        chocolate,          coral,                  cornflowerblue,
    cornsilk,          crimson,            cyan,                   darkblue,
    darkcyan,          darkgoldenrod,      darkgrey,               darkgreen,
    darkkhaki,         darkmagenta,        darkolivegreen,         darkorange,
    darkorchid,        darkred,            darksalmon,             darkseagreen,
    darkslateblue,     darkslategrey,      darkturquoise,          darkviolet,
    deeppink,          deepskyblue,        dimgrey,                dodgerblue,
    firebrick,         floralwhite,        forestgreen,            fuchsia,
    gainsboro,         ghostwhite,         gold,                   goldenrod,
    greenyellow,       honeydew,           hotpink,                indianred,
    indigo,            ivory,              khaki,                  lavender,
    lavenderblush,     lawngreen,          lemonchiffon,           lightblue,
    lightcoral,        lightcyan,          lightgoldenrodyellow,   lightgreen,
    lightgrey,         lightpink,          lightsalmon,            lightseagreen,
    lightskyblue,      lightslategrey,     lightsteelblue,         lightyellow,
    lime,              limegreen,          linen,                  magenta,
    maroon,            mediumaquamarine,   mediumblue,             mediumorchid,
    mediumpurple,      mediumseagreen,     mediumslateblue,        mediumspringgreen,
    mediumturquoise,   mediumvioletred,    midnightblue,           mintcream,
    mistyrose,         moccasin,           navajowhite,            navy,
    oldlace,           olive,              olivedrab,              orange,
    orangered,         orchid,             palegoldenrod,          palegreen,
    paleturquoise,     palevioletred,      papayawhip,             peachpuff,
    peru,              pink,               plum,                   powderblue,
    purple,            rebeccapurple,      rosybrown,              royalblue,
    saddlebrown,       salmon,             sandybrown,             seagreen,
    seashell,          sienna,             silver,                 skyblue,
    slateblue,         slategrey,          snow,                   springgreen,
    steelblue,         tan,                teal,                   thistle,
    tomato,            turquoise,          violet,                 wheat,
    whitesmoke,        yellowgreen;

    /** Attempts to look up a string in the list of known colour names, and return
        the appropriate colour.
        A non-case-sensitive search is made of the list of predefined colours, and
        if a match is found, that colour is returned. If no match is found, the
        colour passed in as the defaultColour parameter is returned.
    */
    static Colour findColourForName (const std::string& colourName, Colour defaultColour);

private:
    //==============================================================================
    // this isn't a class you should ever instantiate - it's just here for the static values in it.
    Colours();
};

#endif //SQUAREPINE_COLOURS_H
