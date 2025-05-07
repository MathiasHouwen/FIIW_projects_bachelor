{-# LANGUAGE OverloadedStrings #-}

import Graphics.UI.Threepenny.Core
import qualified Graphics.UI.Threepenny as UI
import Data.IORef
import Control.Monad (void)

main :: IO ()
main = startGUI defaultConfig { jsStatic = Just "static" } setup

setup :: Window -> UI ()
setup window = do
    return window # set title "Haskell Cookie Clicker"

    -- Game state
    cookiesRef      <- liftIO $ newIORef (0 :: Int)
    clickPowerRef   <- liftIO $ newIORef (1 :: Int)
    autoClickersRef <- liftIO $ newIORef (0 :: Int)

    -- UI Elements
    btnCookie     <- UI.button #+ [string "🍪 Click Cookie!"]
    lblCookies    <- UI.span   # set text "Cookies: 0"
    btnBuyClicker <- UI.button #+ [string "Buy Auto-Clicker (Cost: 50)"]
    btnUpgrade    <- UI.button #+ [string "Upgrade Click (Cost: 25)"]

    -- Timer for passive income
    timer <- UI.timer # set UI.interval 1000
    UI.start timer

    -- Layout
    getBody window #+ [ column
        [ element lblCookies
        , element btnCookie
        , UI.hr
        , element btnBuyClicker
        , element btnUpgrade
        ]
        ]

    -- Manual clicking
    on UI.click btnCookie $ \_ -> do
        clickPower <- liftIO $ readIORef clickPowerRef
        liftIO $ modifyIORef cookiesRef (+ clickPower)
        updateLabel cookiesRef lblCookies

    -- Buy auto-clicker
    on UI.click btnBuyClicker $ \_ -> do
        cookies <- liftIO $ readIORef cookiesRef
        if cookies >= 50
          then do
            liftIO $ modifyIORef cookiesRef (subtract 50)
            liftIO $ modifyIORef autoClickersRef (+1)
            updateLabel cookiesRef lblCookies
          else return ()

    -- Upgrade click power
    on UI.click btnUpgrade $ \_ -> do
        cookies <- liftIO $ readIORef cookiesRef
        if cookies >= 25
          then do
            liftIO $ modifyIORef cookiesRef (subtract 25)
            liftIO $ modifyIORef clickPowerRef (+1)
            updateLabel cookiesRef lblCookies
          else return ()

    -- Passive income from auto-clickers
    on UI.tick timer $ \_ -> do
        autoClickers <- liftIO $ readIORef autoClickersRef
        liftIO $ modifyIORef cookiesRef (+ autoClickers)
        updateLabel cookiesRef lblCookies


updateLabel :: IORef Int -> Element -> UI ()
updateLabel ref label = do
    val <- liftIO $ readIORef ref
    textNode <- string ("Cookies: " ++ show val)
    void $ element label # set children [textNode]