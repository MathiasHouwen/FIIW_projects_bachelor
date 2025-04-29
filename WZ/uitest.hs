import qualified Graphics.UI.Threepenny as UI
import Graphics.UI.Threepenny.Core
import System.Random (randomRIO)

main :: IO ()
main = startGUI defaultConfig { jsStatic = Just "static" } setup

setup :: Window -> UI ()
setup window = do
    return window # set title "Moving Square"

    square <- UI.div # set UI.style
        [ ("width", "100px")
        , ("height", "100px")
        , ("background", "skyblue")
        , ("position", "absolute")
        , ("left", "50px")
        , ("top", "50px")
        , ("cursor", "pointer")
        , ("border", "2px solid black")
        ]

    on UI.click square $ \_ -> do
        x :: Int <- liftIO $ randomRIO (0, 1500)
        y :: Int <- liftIO $ randomRIO (0, 700)
        element square # set UI.style
            [ ("width", "100px")
            , ("height", "100px")
            , ("background", "skyblue")
            , ("position", "absolute")
            , ("left", show x ++ "px")
            , ("top", show y ++ "px")
            , ("cursor", "pointer")
            , ("border", "2px solid black")
            ]

    getBody window #+ [element square]
    return ()
