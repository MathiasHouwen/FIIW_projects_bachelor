import random
import math

randomNamenEnGeslacht = [
  ["man", "Ebbe Wertz"],
  ["man", "Mathias Houwen"],
  ["man", "Robin Lambregts"],
  ["vrouw", "Sophie Jansen"],
  ["man", "Karel Bakker"],
  ["vrouw", "Lisa Willems"],
  ["man", "Tom Vos"],
  ["vrouw", "Eva de Boer"],
  ["man", "Lucas Mulder"],
  ["vrouw", "Mila Visser"],
  ["man", "Rik Peters"],
  ["vrouw", "Emma van Dijk"],
  ["man", "Henk Kuipers"],
  ["vrouw", "Sara van Dam"],
  ["man", "Bart Meijer"],
  ["vrouw", "Fleur van Leeuwen"],
  ["man", "Wim Schouten"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Joost Hendriks"],
  ["vrouw", "Noa de Graaf"],
  ["man", "Bas van der Meer"],
  ["vrouw", "Isa Timmermans"],
  ["man", "Dirk van den Berg"],
  ["vrouw", "Zoe de Lange"],
  ["man", "Erik de Bruin"],
  ["vrouw", "Roos Bakker"],
  ["man", "Mark van Loon"],
  ["vrouw", "Amber Smeets"],
  ["man", "Frank van Vliet"],
  ["vrouw", "Lieke van der Veen"],
  ["man", "Leo Molenaar"],
  ["vrouw", "Tessa van der Wal"],
  ["man", "Jan Willem de Groot"],
  ["vrouw", "Julia van den Heuvel"],
  ["man", "Hans de Vos"],
  ["vrouw", "Nina van der Heijden"],
  ["man", "Ruben van Dam"],
  ["vrouw", "Sanne de Ruiter"],
  ["man", "Paul van der Linden"],
  ["vrouw", "Mara de Koning"],
  ["man", "Arjen van den Bosch"],
  ["vrouw", "Laura de Wit"],
  ["man", "Geert de Haan"],
  ["vrouw", "Lena van der Berg"],
  ["man", "Wouter de Boer"],
  ["vrouw", "Maud de Jong"],
  ["man", "Stefan van der Meer"],
  ["vrouw", "Elise van der Laan"],
  ["man", "Thijs Jansen"],
  ["vrouw", "Bo de Vries"],
  ["man", "Lars de Koning"],
  ["vrouw", "Lana van Dijk"],
  ["man", "Martijn van Beek"],
  ["vrouw", "Iris de Graaf"],
  ["man", "Niels de Lange"],
  ["vrouw", "Livia van der Veen"],
  ["man", "Bert de Groot"],
  ["vrouw", "Yara van Dam"],
  ["man", "Koen van Vliet"],
  ["vrouw", "Tara van Leeuwen"],
  ["man", "Dennis de Bruin"],
  ["vrouw", "Elena van den Berg"],
  ["man", "Jeroen van der Wal"],
  ["vrouw", "Lara van der Laan"],
  ["man", "Michiel de Ruiter"],
  ["vrouw", "Mette van der Linden"],
  ["man", "Jelle de Wit"],
  ["vrouw", "Leah van Beek"],
  ["man", "Sander de Jong"],
  ["vrouw", "Nadine van der Heuvel"],
  ["man", "Maarten de Graaf"],
  ["vrouw", "Eline de Boer"],
  ["man", "Bram van Dijk"],
  ["vrouw", "Jade van Dam"],
  ["man", "Victor de Lange"],
  ["vrouw", "Nienke de Vries"],
  ["man", "Gijs van der Meer"],
  ["vrouw", "Myrthe van der Veen"],
  ["man", "Ronald de Groot"],
  ["vrouw", "Linde van der Heijden"],
  ["man", "Roy van Dam"],
  ["vrouw", "Silke de Bruin"],
  ["man", "Pim van der Wal"],
  ["vrouw", "Livia de Koning"],
  ["man", "Dirk van der Linden"],
  ["vrouw", "Lara van der Laan"],
  ["man", "Bas van Dijk"],
  ["vrouw", "Sophie de Vries"],
  ["man", "Erwin de Jong"],
  ["vrouw", "Eva van Beek"],
  ["man", "Rob de Wit"],
  ["vrouw", "Noor van der Heuvel"],
  ["man", "Arnold de Graaf"],
  ["vrouw", "Isa de Boer"],
  ["man", "Theo van der Veen"],
  ["vrouw", "Sanne van der Heijden"],
  ["man", "Casper de Groot"],
  ["vrouw", "Lotte van Dam"],
  ["man", "Patrick de Vries"],
  ["vrouw", "Kim van Beek"],
  ["man", "Tim van der Linden"],
  ["vrouw", "Esmee de Wit"],
  ["man", "Joris van den Berg"],
  ["vrouw", "Lise de Graaf"],
  ["man", "Vincent van Dijk"],
  ["vrouw", "Demi van der Heijden"],
  ["man", "Mart de Koning"],
  ["vrouw", "Fien de Bruin"],
  ["man", "Floris van Dam"],
  ["vrouw", "Saar de Groot"],
  ["man", "Rik de Vries"],
  ["vrouw", "Mila van den Heuvel"],
  ["man", "Guus van der Wal"],
  ["vrouw", "Noor de Boer"],
  ["man", "Jochem de Wit"],
  ["vrouw", "Elin van der Linden"],
  ["man", "Sebastiaan de Graaf"],
  ["vrouw", "Fay van Dam"],
  ["man", "Teun van Dijk"],
  ["vrouw", "Lise de Jong"],
  ["man", "Cas de Lange"],
  ["vrouw", "Jasmijn van der Meer"],
  ["man", "Mick van der Heijden"],
  ["vrouw", "Bo de Vries"],
  ["man", "Kees van Beek"],
  ["vrouw", "Nina de Bruin"],
  ["man", "Sjoerd de Groot"],
  ["vrouw", "Amy van Dam"],
  ["man", "Daan de Vries"],
  ["vrouw", "Iris van der Heijden"],
  ["man", "Hugo van der Wal"],
  ["vrouw", "Lena de Wit"],
  ["man", "Gert van der Linden"],
  ["vrouw", "Mara de Koning"],
  ["man", "Job de Graaf"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Ruben van der Meer"],
  ["vrouw", "Lieke de Jong"],
  ["man", "Koen de Wit"],
  ["vrouw", "Tess van Beek"],
  ["man", "Thomas de Bruin"],
  ["vrouw", "Luna van der Heijden"],
  ["man", "Sam van Dam"],
  ["vrouw", "Tessa van der Wal"],
  ["man", "Jasper van Dijk"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Steven de Graaf"],
  ["vrouw", "Sophie de Koning"],
  ["man", "Wout van der Linden"],
  ["vrouw", "Eva van Beek"],
  ["man", "Dirk van der Veen"],
  ["vrouw", "Lina de Bruin"],
  ["man", "Ralph de Groot"],
  ["vrouw", "Mila van Dijk"],
  ["man", "Hendrik de Vries"],
  ["vrouw", "Anne van der Heijden"],
  ["man", "Boris de Jong"],
  ["vrouw", "Nina van der Wal"],
  ["man", "Victor de Wit"],
  ["vrouw", "Noa de Vries"],
  ["man", "Arjen van Dijk"],
  ["vrouw", "Sara van Beek"],
  ["man", "Rik de Graaf"],
  ["vrouw", "Maud de Bruin"],
  ["man", "Frank de Groot"],
  ["vrouw", "Roos van der Meer"],
  ["man", "Luuk van der Heijden"],
  ["vrouw", "Lara de Jong"],
  ["man", "Harm de Wit"],
  ["vrouw", "Emma van Beek"],
  ["man", "Timo de Vries"],
  ["vrouw", "Yara de Bruin"],
  ["man", "Mark van Dam"],
  ["vrouw", "Mette de Vries"],
  ["man", "Koen van der Heijden"],
  ["vrouw", "Saar de Graaf"],
  ["man", "Erik de Groot"],
  ["vrouw", "Linde de Wit"],
  ["man", "Joost van Dijk"],
  ["vrouw", "Tessa van Dam"],
  ["man", "Stijn de Vries"],
  ["vrouw", "Fleur van der Wal"],
  ["man", "Bas van der Linden"],
  ["vrouw", "Noa de Wit"],
  ["man", "Hugo van Beek"],
  ["vrouw", "Eva de Graaf"],
  ["man", "Rik van der Heijden"],
  ["vrouw", "Lara de Vries"],
  ["man", "Sander van Dam"],
  ["vrouw", "Julia de Groot"],
  ["man", "Joris de Bruin"],
  ["vrouw", "Iris van der Linden"],
  ["man", "Thijs de Vries"],
  ["vrouw", "Sanne van Beek"],
  ["man", "Lars de Jong"],
  ["vrouw", "Tara van der Meer"],
  ["man", "Wouter de Wit"],
  ["vrouw", "Sophie van der Heijden"],
  ["man", "Niels van Dam"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Casper van der Wal"],
  ["vrouw", "Bo van der Linden"],
  ["man", "Luuk de Wit"],
  ["vrouw", "Mila de Graaf"],
  ["man", "Bram de Groot"],
  ["vrouw", "Noa van Dijk"],
  ["man", "Ruben de Bruin"],
  ["vrouw", "Lara van Beek"],
  ["man", "Maarten de Vries"],
  ["vrouw", "Sara van Dam"],
  ["man", "Tim van der Linden"],
  ["vrouw", "Eva de Jong"],
  ["man", "Jan de Wit"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Klaas van der Heijden"],
  ["vrouw", "Vera de Bruin"],
  ["man", "Jeroen de Graaf"],
  ["vrouw", "Nina van Dijk"],
  ["man", "Sjoerd van Dam"],
  ["vrouw", "Fay de Vries"],
  ["man", "Leon van der Meer"],
  ["vrouw", "Mila van der Wal"],
  ["man", "Jules van Beek"],
  ["vrouw", "Lies van der Heijden"],
  ["man", "Ties de Wit"],
  ["vrouw", "Lina van Dam"],
  ["man", "Ron de Jong"],
  ["vrouw", "Anne de Graaf"],
  ["man", "Chris van Dijk"],
  ["vrouw", "Lana de Vries"],
  ["man", "Patrick van der Linden"],
  ["vrouw", "Yara van der Heijden"],
  ["man", "Gert van der Meer"],
  ["vrouw", "Demi van Dijk"],
  ["man", "Niek van Dam"],
  ["vrouw", "Julia de Vries"],
  ["man", "Mike de Bruin"],
  ["vrouw", "Evy van Beek"],
  ["man", "Erwin van der Wal"],
  ["vrouw", "Jade de Jong"],
  ["man", "Roel de Graaf"],
  ["vrouw", "Luna van Dam"],
  ["man", "Kasper de Vries"],
  ["vrouw", "Demi de Bruin"],
  ["man", "Joep van der Linden"],
  ["vrouw", "Lara de Wit"],
  ["man", "Daan van Dijk"],
  ["vrouw", "Noa van Beek"],
  ["man", "Twan de Bruin"],
  ["vrouw", "Fleur van der Heijden"],
  ["man", "Bert van Dam"],
  ["vrouw", "Nina de Groot"],
  ["man", "Roy de Graaf"],
  ["vrouw", "Elise van Beek"],
  ["man", "Kees de Jong"],
  ["vrouw", "Mila de Wit"],
  ["man", "Jan van der Heijden"],
  ["vrouw", "Sara van der Veen"],
  ["man", "Wim van Dijk"],
  ["vrouw", "Eline van Dam"],
  ["man", "Pieter de Bruin"],
  ["vrouw", "Sophie van der Wal"],
  ["man", "Bart van der Linden"],
  ["vrouw", "Roos de Vries"],
  ["man", "Rik de Groot"],
  ["vrouw", "Sanne de Jong"],
  ["man", "Frank van der Heijden"],
  ["vrouw", "Lara de Vries"],
  ["man", "Teun de Graaf"],
  ["vrouw", "Jasmijn van Dijk"],
  ["man", "Hendrik van Dam"],
  ["vrouw", "Eva de Wit"],
  ["man", "Mark de Bruin"],
  ["vrouw", "Nina van der Linden"],
  ["man", "Dirk van der Heijden"],
  ["vrouw", "Lisa de Vries"],
  ["man", "Vincent de Jong"],
  ["vrouw", "Mara van Dijk"],
  ["man", "Jeroen de Bruin"],
  ["vrouw", "Lena van der Heijden"],
  ["man", "Timo van Dam"],
  ["vrouw", "Sara de Graaf"],
  ["man", "Stijn van der Meer"],
  ["vrouw", "Fleur van Dijk"],
  ["man", "Wim de Vries"],
  ["vrouw", "Tessa de Wit"],
  ["man", "Niek van der Heijden"],
  ["vrouw", "Lise de Bruin"],
  ["man", "Gert de Jong"],
  ["vrouw", "Eva van der Linden"],
  ["man", "Hugo de Graaf"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Ruben van der Heijden"],
  ["vrouw", "Julia van Dam"],
  ["man", "Niels de Wit"],
  ["vrouw", "Lara de Bruin"],
  ["man", "Bram de Graaf"],
  ["vrouw", "Sara van Beek"],
  ["man", "Wouter van Dijk"],
  ["vrouw", "Lise van der Heijden"],
  ["man", "Dirk van Dam"],
  ["vrouw", "Tessa van der Veen"],
  ["man", "Frank van der Wal"],
  ["vrouw", "Mila de Bruin"],
  ["man", "Rik van der Linden"],
  ["vrouw", "Bo van Dam"],
  ["man", "Teun de Vries"],
  ["vrouw", "Lotte van der Heijden"],
  ["man", "Thijs de Bruin"],
  ["vrouw", "Sara de Vries"],
  ["man", "Erik van Dam"],
  ["vrouw", "Yara de Jong"],
  ["man", "Niek van der Veen"],
  ["vrouw", "Nina van der Heijden"],
  ["man", "Victor de Bruin"],
  ["vrouw", "Sophie de Graaf"],
  ["man", "Sjoerd van der Linden"],
  ["vrouw", "Jade de Vries"],
  ["man", "Ron de Bruin"],
  ["vrouw", "Lina van Dam"],
  ["man", "Koen de Graaf"],
  ["vrouw", "Elise de Vries"],
  ["man", "Bart van der Heijden"],
  ["vrouw", "Tessa van Dam"],
  ["man", "Pim van der Linden"],
  ["vrouw", "Lara de Bruin"],
  ["man", "Erwin van Dam"],
  ["vrouw", "Nina van Dijk"],
  ["man", "Harm van der Heijden"],
  ["vrouw", "Lies van Dam"],
  ["man", "Victor de Graaf"],
  ["vrouw", "Eva van der Linden"],
  ["man", "Thijs van Dam"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Dirk de Bruin"],
  ["vrouw", "Mila van Dijk"],
  ["man", "Erik de Vries"],
  ["vrouw", "Lotte de Bruin"],
  ["man", "Hugo van der Heijden"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Jan van Dam"],
  ["vrouw", "Bo de Jong"],
  ["man", "Tim de Graaf"],
  ["vrouw", "Sophie van der Linden"],
  ["man", "Rik de Bruin"],
  ["vrouw", "Sara van der Wal"],
  ["man", "Maarten de Wit"],
  ["vrouw", "Elise van Dam"],
  ["man", "Timo de Jong"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Wim de Bruin"],
  ["vrouw", "Eva van der Heijden"],
  ["man", "Gijs van Dam"],
  ["vrouw", "Mila de Jong"],
  ["man", "Jeroen de Wit"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Frank van Dam"],
  ["vrouw", "Lotte van der Linden"],
  ["man", "Hugo de Bruin"],
  ["vrouw", "Sara de Wit"],
  ["man", "Teun van der Heijden"],
  ["vrouw", "Jade van Dam"],
  ["man", "Rik van der Veen"],
  ["vrouw", "Fleur de Bruin"],
  ["man", "Victor van der Heijden"],
  ["vrouw", "Eva de Vries"],
  ["man", "Tim de Wit"],
  ["vrouw", "Sophie van Dam"],
  ["man", "Erik de Bruin"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Frank de Vries"],
  ["vrouw", "Mila de Graaf"],
  ["man", "Hugo van der Heijden"],
  ["vrouw", "Sara de Bruin"],
  ["man", "Dirk van Dam"],
  ["vrouw", "Lise de Wit"],
  ["man", "Thijs de Vries"],
  ["vrouw", "Eva van der Heijden"],
  ["man", "Niels de Bruin"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Rik van Dam"],
  ["vrouw", "Tessa de Wit"],
  ["man", "Victor de Bruin"],
  ["vrouw", "Sophie van der Heijden"],
  ["man", "Erik van Dam"],
  ["vrouw", "Mila de Graaf"],
  ["man", "Hugo de Jong"],
  ["vrouw", "Lotte van Dijk"],
  ["man", "Thijs van der Linden"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Dirk de Bruin"],
  ["vrouw", "Fleur van der Heijden"],
  ["man", "Niels de Vries"],
  ["vrouw", "Eva de Bruin"],
  ["man", "Rik van der Heijden"],
  ["vrouw", "Lotte van Dam"],
  ["man", "Victor van der Linden"],
  ["vrouw", "Sophie de Graaf"],
  ["man", "Erik de Vries"],
  ["vrouw", "Mila van der Heijden"],
  ["man", "Hugo de Bruin"],
  ["vrouw", "Sara van Dam"],
  ["man", "Thijs van Dijk"],
  ["vrouw", "Eva de Vries"],
  ["man", "Niels van der Heijden"],
  ["vrouw", "Lotte de Wit"],
  ["man", "Dirk van der Heijden"],
  ["vrouw", "Sanne de Bruin"],
  ["man", "Rik de Vries"],
  ["vrouw", "Fleur van Dam"],
  ["man", "Victor de Wit"],
  ["vrouw", "Lotte de Bruin"],
  ["man", "Erik van der Heijden"],
  ["vrouw", "Mila de Vries"],
  ["man", "Hugo van Dam"],
  ["vrouw", "Sara de Bruin"],
  ["man", "Thijs van der Heijden"],
  ["vrouw", "Eva de Wit"],
  ["man", "Niels de Graaf"],
  ["vrouw", "Lotte van der Veen"],
  ["man", "Dirk van Dam"],
  ["vrouw", "Sanne van der Heijden"],
  ["man", "Rik van der Linden"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Victor van Dijk"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Erik de Bruin"],
  ["vrouw", "Mila de Vries"],
  ["man", "Hugo de Graaf"],
  ["vrouw", "Sara van der Heijden"],
  ["man", "Thijs de Wit"],
  ["vrouw", "Eva van Dam"],
  ["man", "Niels de Bruin"],
  ["vrouw", "Lotte van der Heijden"],
  ["man", "Dirk de Graaf"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Rik de Wit"],
  ["vrouw", "Fleur van der Linden"],
  ["man", "Victor van Dam"],
  ["vrouw", "Lotte de Bruin"],
  ["man", "Erik van der Heijden"],
  ["vrouw", "Mila de Graaf"],
  ["man", "Hugo van der Veen"],
  ["vrouw", "Sara van Dam"],
  ["man", "Thijs de Vries"],
  ["vrouw", "Eva de Bruin"],
  ["man", "Niels van Dijk"],
  ["vrouw", "Lotte de Wit"],
  ["man", "Dirk van der Heijden"],
  ["vrouw", "Sanne de Graaf"],
  ["man", "Rik van der Veen"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Victor de Bruin"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Erik van Dam"],
  ["vrouw", "Mila van der Heijden"],
  ["man", "Hugo de Graaf"],
  ["vrouw", "Sara de Vries"],
  ["man", "Thijs van der Linden"],
  ["vrouw", "Eva de Wit"],
  ["man", "Niels de Bruin"],
  ["vrouw", "Lotte van Dam"],
  ["man", "Dirk van der Veen"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Rik van Dam"],
  ["vrouw", "Fleur de Bruin"],
  ["man", "Victor van der Heijden"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Erik de Wit"],
  ["vrouw", "Mila van Dam"],
  ["man", "Hugo van der Linden"],
  ["vrouw", "Sara de Bruin"],
  ["man", "Thijs van der Veen"],
  ["vrouw", "Eva de Vries"],
  ["man", "Niels van der Heijden"],
  ["vrouw", "Lotte de Graaf"],
  ["man", "Dirk de Vries"],
  ["vrouw", "Sanne van Dam"],
  ["man", "Rik de Bruin"],
  ["vrouw", "Fleur van der Linden"],
  ["man", "Victor de Graaf"],
  ["vrouw", "Lotte van Dijk"],
  ["man", "Erik de Vries"],
  ["vrouw", "Mila van der Heijden"],
  ["man", "Hugo de Bruin"],
  ["vrouw", "Sara van Dam"],
  ["man", "Thijs van Dam"],
  ["vrouw", "Eva van der Heijden"],
  ["man", "Niels van Dijk"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Dirk de Wit"],
  ["vrouw", "Sanne van der Veen"],
  ["man", "Rik van der Heijden"],
  ["vrouw", "Fleur de Bruin"],
  ["man", "Victor van der Linden"],
  ["vrouw", "Lotte van Dam"],
  ["man", "Erik van Dijk"],
  ["vrouw", "Mila de Vries"],
  ["man", "Hugo de Wit"],
  ["vrouw", "Sara de Graaf"],
  ["man", "Thijs de Bruin"],
  ["vrouw", "Eva de Vries"],
  ["man", "Niels van der Veen"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Dirk de Bruin"],
  ["vrouw", "Sanne van Dam"],
  ["man", "Rik van Dam"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Victor de Jong"],
  ["vrouw", "Lotte van der Heijden"],
  ["man", "Erik van der Veen"],
  ["vrouw", "Mila de Wit"],
  ["man", "Hugo van Dijk"],
  ["vrouw", "Sara van der Linden"],
  ["man", "Thijs van der Heijden"],
  ["vrouw", "Eva de Graaf"],
  ["man", "Niels de Wit"],
  ["vrouw", "Lotte de Bruin"],
  ["man", "Dirk van der Linden"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Rik de Graaf"],
  ["vrouw", "Fleur van Dam"],
  ["man", "Victor van der Veen"],
  ["vrouw", "Lotte van der Linden"],
  ["man", "Erik van der Heijden"],
  ["vrouw", "Mila de Vries"],
  ["man", "Hugo de Bruin"],
  ["vrouw", "Sara de Wit"],
  ["man", "Thijs van der Veen"],
  ["vrouw", "Eva van der Heijden"],
  ["man", "Niels van Dam"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Dirk de Vries"],
  ["vrouw", "Sanne van der Linden"],
  ["man", "Rik van Dijk"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Victor de Graaf"],
  ["vrouw", "Lotte van der Heijden"],
  ["man", "Erik van Dam"],
  ["vrouw", "Mila van Dam"],
  ["man", "Hugo de Graaf"],
  ["vrouw", "Sara van der Veen"],
  ["man", "Thijs de Vries"],
  ["vrouw", "Eva van Dijk"],
  ["man", "Niels de Bruin"],
  ["vrouw", "Lotte de Wit"],
  ["man", "Dirk van Dam"],
  ["vrouw", "Sanne de Bruin"],
  ["man", "Rik de Vries"],
  ["vrouw", "Fleur van der Linden"],
  ["man", "Victor van Dam"],
  ["vrouw", "Lotte de Bruin"],
  ["man", "Erik de Jong"],
  ["vrouw", "Mila de Graaf"],
  ["man", "Hugo van der Heijden"],
  ["vrouw", "Sara de Vries"],
  ["man", "Thijs de Graaf"],
  ["vrouw", "Eva van der Linden"],
  ["man", "Niels de Vries"],
  ["vrouw", "Lotte van der Heijden"],
  ["man", "Dirk van Dijk"],
  ["vrouw", "Sanne de Vries"],
  ["man", "Rik de Bruin"],
  ["vrouw", "Fleur van Dam"],
  ["man", "Victor de Wit"],
  ["vrouw", "Lotte de Graaf"],
  ["man", "Erik de Vries"],
  ["vrouw", "Mila van der Heijden"],
  ["man", "Hugo van Dam"],
  ["vrouw", "Sara de Bruin"],
  ["man", "Thijs van der Veen"],
  ["vrouw", "Eva van Dijk"],
  ["man", "Niels de Wit"],
  ["vrouw", "Lotte de Vries"],
  ["man", "Dirk van der Linden"],
  ["vrouw", "Sanne van der Heijden"],
  ["man", "Rik van Dam"],
  ["vrouw", "Fleur de Vries"],
  ["man", "Victor de Bruin"],
  ["vrouw", "Lotte de Jong"],
  ["man", "Erik van der Heijden"],
  ["vrouw", "Mila de Vries"],
  ["man", "Hugo de Graaf"]
]


def is_power_of_two(n):
    return (n & (n - 1) == 0) and n != 0

def verdeelSpelers(aantalSpelers):
    for aantalMatches in range(1, aantalSpelers // 2 + 1):
        spelersInMatch = aantalMatches*2
        spelersVrijgesteld = aantalSpelers - spelersInMatch
        winnaars = aantalMatches
        spelersNaRonde = winnaars + spelersVrijgesteld
        
        if is_power_of_two(spelersNaRonde):
            aantalRondes = int(math.log2(spelersNaRonde))+1
            return spelersVrijgesteld, aantalRondes
    return 0

speler_id = 0
toernooi_id = 0
reeks_id = 0
match_id = 0

toernoois = []
reeksen = []
matchen = []
spelers = []
deelnames = []

#======================
#   CLUBS
#======================
tennisclubs = [
    {'id':0, 'naam':'Tennis_Diepenbeek',        'locatie':'Diepenbeek'},
    {'id':1, 'naam':'Sport-Hasselt tennis',     'locatie':'Hasselt'},
    {'id':2, 'naam':'Club Gent',                'locatie':'Gent'},
    {'id':3, 'naam':'Ant Werpt',                'locatie':'Antwerpen'},
    {'id':4, 'naam':'Brugse_Tennis_Vereniging', 'locatie':'Brugge'},
    {'id':5, 'naam':'Tennis_Lommel',            'locatie':'Lommel'},
    {'id':6, 'naam':'Aalst Tennis Club',        'locatie':'Aalst'}
]
#======================
#   Spelers
#======================
def genSpelers(spelersLijst, spelerID):
    for club in tennisclubs:
        aantal =  random.randint(25,50)
        spelersVanClub = []
        nummer = 0
        for _ in range(aantal):
            leeftijd = random.randint(5,30)
            email = f"speler{spelerID}@example.com"
            geslacht = randomNamenEnGeslacht[spelerID][0]
            naam = randomNamenEnGeslacht[spelerID][1]
            if spelerID == 0:
                leeftijd = 19
                email = "ebbe.wertz@student.uhasselt.be"
            if spelerID == 1:
                leeftijd = 19
                email = "mathias.houwen@student.uhasselt.be"
            if spelerID == 2:
                leeftijd = 19
                email = "robin.lambregts@student.uhasselt.be"
            speler = {
                'persoonlijk_naam':naam,
                'id':spelerID,
                'persoonlijk_email':email,
                "fysiek_leeftijd":leeftijd,
                "fysiek_geslacht":geslacht,
                "nummer":nummer,
                "tennisclub_id":club['id'],
                'hoogste ranking':0,
                'aantal gespeelde matches': 0,
                'aantal gewonnen matches': 0}
            spelersVanClub.append(speler)
            spelersLijst.append(speler)
            nummer += 1
            spelerID += 1
        club["_spelers"] = spelersVanClub
    return spelersLijst, spelerID

succes = False
while not succes:
    spelers = []
    speler_id = 0
    spelers, speler_id = genSpelers(spelers, speler_id)

    gr1 = [x for x in spelers if x["fysiek_leeftijd"] >= 5 and x["fysiek_leeftijd"] <= 10 and x["fysiek_geslacht"] == "man"]
    gr2 = [x for x in spelers if x["fysiek_leeftijd"] >= 5 and x["fysiek_leeftijd"] <= 10 and x["fysiek_geslacht"] == "vrouw"]
    gr3 = [x for x in spelers if x["fysiek_leeftijd"] >= 11 and x["fysiek_leeftijd"] <= 17 and x["fysiek_geslacht"] == "man"]
    gr4 = [x for x in spelers if x["fysiek_leeftijd"] >= 11 and x["fysiek_leeftijd"] <= 17 and x["fysiek_geslacht"] == "vrouw"]
    gr5 = [x for x in spelers if x["fysiek_leeftijd"] >= 18 and x["fysiek_geslacht"] == "man"]
    gr6 = [x for x in spelers if x["fysiek_leeftijd"] >= 18 and x["fysiek_geslacht"] == "vrouw"]

    succes = True

    for gr in [gr1, gr2, gr3, gr4, gr5, gr6]:
        if(len(gr) < 21):
            succes = False
            print("spelers opnieuw aan het genereren omdat een leeftijd-geslacht groep te klein is voor maximale reeksdeelnemers aantal")
    
#======================
#   Toernooien
#======================
for club in tennisclubs:
    #elke club organiseert 0-3 toernooien
    aantal =  random.randint(0,2)
    for _ in range(aantal):
        gespeeld = random.choice([1, 1, 1, 0])
        leider = random.choice(club["_spelers"])
        jaar = random.randint(2020,2023) if gespeeld else 2025
        maand = random.randint(1,12)
        dag = random.randint(1,30)
        toernooi = {'id': toernooi_id, 'datum':f"{jaar}-{maand}-{dag}",'tennisclub_id':club.get('id'), "wedstrijdleider_id":leider['id']}
        toernooi['_gespeeld'] = gespeeld
        toernooi_id += 1
        toernoois.append(toernooi)
#======================
#   Reeksen
#======================
for toernooi in toernoois:
    gespeeld = toernooi['_gespeeld']
    
    #volwassenen
    reeksen.append({'leeftijdsgroep':'18+', 'geslacht':'man', 'id':reeks_id, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
    reeksen.append({'leeftijdsgroep':'18+', 'geslacht':'vrouw', 'id':reeks_id+1, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
    reeks_id += 2
    #50% kans voor ook kinder reeksen
    if random.choice([True, False]):
        reeksen.append({'leeftijdsgroep':'5-10', 'geslacht':'man', 'id':reeks_id, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
        reeksen.append({'leeftijdsgroep':'5-10', 'geslacht':'vrouw', 'id':reeks_id+1, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
        reeksen.append({'leeftijdsgroep':'11-17', 'geslacht':'man', 'id':reeks_id+2, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
        reeksen.append({'leeftijdsgroep':'11-17', 'geslacht':'vrouw', 'id':reeks_id+3, 'toernooi_id':toernooi.get('id'), 'gespeeld':gespeeld})
        reeks_id += 4

#======================
#   Matchen en deelnames
#======================
def checkLeeftijd(l, lgroepString):
    if lgroepString == '18+': return l >= 18
    onder, boven = [int(n) for n in lgroepString.split('-')]
    return l >= onder and l <= boven

#er zijn reeksen aangeduid als gespeeld. Alleen deze hebben matchen.
#de andere blijven leeg om een inschrijving te kunnen maken
gespeeldeReeksen = [r for r in reeksen if r['gespeeld'] == 1]

for reeks in gespeeldeReeksen:

    alleSpelersQualifiedVoorReeks = [s for s in spelers if s['fysiek_geslacht'] == reeks['geslacht'] and checkLeeftijd(s['fysiek_leeftijd'], reeks['leeftijdsgroep'])]

    beginAantalSpelers = random.randint(6,20)
    vrij, aantalRondes = verdeelSpelers(beginAantalSpelers)    


    spelersInRonde = random.sample(alleSpelersQualifiedVoorReeks, beginAantalSpelers)
    alleSpelersDieNietInDezeReeksZitten = [s for s in spelers if s not in spelersInRonde]
    

    for ronde in range(1,aantalRondes+1):

        vrijgesteldeSpelers = []
        if vrij > 0:
            vrijgesteldeSpelers = random.sample(spelersInRonde, vrij)
            for speler in vrijgesteldeSpelers:
                deelnames.append({'speler_id':speler['id'], 'match_id':match_id, 'score':0, 'vrijstelling':1})


        random.shuffle(spelersInRonde)
        spelersInMatchen = [s for s in spelersInRonde if s not in vrijgesteldeSpelers]
        aantalMatchen = len(spelersInMatchen) // 2

        spelerIndex = 0

        verliezers = []

        for _ in range(aantalMatchen):

            scheidsRechter = random.choice(alleSpelersDieNietInDezeReeksZitten)
            match = {'id':match_id, 'ronde':ronde, 'reeks_id':reeks['id'], 'scheidsrechter_id':"NULL"}
            if(ronde >= aantalRondes - 1):
                match['scheidsrechter_id'] = scheidsRechter['id']
            matchen.append(match)
            match_id += 1

            speler1 = spelersInMatchen[spelerIndex]
            speler2 = spelersInMatchen[spelerIndex+1]
            speler1['aantal gespeelde matches'] = speler1['aantal gespeelde matches'] + 1
            speler2['aantal gespeelde matches'] = speler2['aantal gespeelde matches'] + 1
            if ronde > speler1['hoogste ranking']: speler1['hoogste ranking'] = ronde
            if ronde > speler2['hoogste ranking']: speler2['hoogste ranking'] = ronde
            spelerIndex += 2

            score1 = random.randint(3,10)
            score2 = random.randint(3,10)
            if(score1 == score2): score2 += 1
            verliezer = speler1 if score1 < score2 else speler2
            winnaar = speler1 if score1 > score2 else speler2
            winnaar['aantal gewonnen matches'] = winnaar['aantal gewonnen matches'] + 1

            deelnames.append({'speler_id':speler1['id'], 'match_id':match['id'], 'score':score1, 'vrijstelling':0})
            deelnames.append({'speler_id':speler2['id'], 'match_id':match['id'], 'score':score2, 'vrijstelling':0})



            verliezers.append(verliezer)

        for verliezer in verliezers:
            spelersInRonde.remove(verliezer)

        vrij = 0

def wr(file, string, index, list):
    end = ',' if index < len(list) - 1 else ';'
    file.write(string + end + '\n')

with open('Database_Data_Insert.sql', 'w') as file:
    file.write("INSERT INTO `tennisclubs` (`id`, `naam`, `locatie`) VALUES\n")
    [wr(file, f"({c['id']}, '{c['naam']}', '{c['locatie']}')", i, tennisclubs) for i, c in enumerate(tennisclubs)]
    file.write("INSERT INTO `toernoois` (`id`, `tennisclub_id`, `datum`, `wedstrijdleider_id`) VALUES\n")
    [wr(file, f"({t['id']}, {t['tennisclub_id']}, '{t['datum']}', {t['wedstrijdleider_id']})", i, toernoois) for i, t in enumerate(toernoois)]
    file.write("INSERT INTO `reeksen` (`id`, `toernooi_id`, `geslacht`, `leeftijdsgroep`, `gespeeld`) VALUES\n")
    [wr(file, f"({r['id']}, {r['toernooi_id']}, '{r['geslacht']}', '{r['leeftijdsgroep']}', {r['gespeeld']})", i, reeksen) for i, r in enumerate(reeksen)]
    file.write("INSERT INTO `matchen` (`id`, `reeks_id`, `ronde`, `scheidsrechter_id`) VALUES\n")
    [wr(file, f"({m['id']}, {m['reeks_id']}, {m['ronde']}, {m['scheidsrechter_id']})", i, matchen) for i, m in enumerate(matchen)]
    file.write("INSERT INTO `deelnames` (`speler_id`, `match_id`, `score`, `vrijstelling`) VALUES\n")
    [wr(file, f"({d['speler_id']}, {d['match_id']}, {d['score']}, {d['vrijstelling']})", i, deelnames) for i, d in enumerate(deelnames)]
    file.write("INSERT INTO `spelers` (`id`, `nummer`, `hoogste ranking`, `persoonlijk_naam`, `persoonlijk_email`, `fysiek_geslacht`, `fysiek_leeftijd`, `tennisclub_id`, `aantal gespeelde matches`, `aantal gewonnen matches`) VALUES\n")
    [wr(file, f"({s['id']}, {s['nummer']}, {s['hoogste ranking']}, '{s['persoonlijk_naam']}', '{s['persoonlijk_email']}', '{s['fysiek_geslacht']}', {s['fysiek_leeftijd']}, {s['tennisclub_id']}, {s['aantal gespeelde matches']}, {s['aantal gewonnen matches']})", i, spelers) for i, s in enumerate(spelers)]