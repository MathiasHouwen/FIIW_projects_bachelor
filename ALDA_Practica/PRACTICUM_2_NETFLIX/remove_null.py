import pandas as pd

def main(file_name: str):

    lines = []

    inname = f"{file_name}.csv"
    outname = f"{file_name}_zonder_null.csv"

    # remove null
    df = pd.read_csv(inname, encoding="UTF-8")
    df = df.dropna()
    df["releaseYear"] = df["releaseYear"].apply(lambda x: int(x))
    df.to_csv(outname, index=False)

    # titles zoals '71 insluiten in double quotes
    with open(outname, "r", encoding="UTF-8") as file:
        for line in file:
            if line[0] == "'":
                splits = line.split(",", 1)
                line = f"\"{splits[0]}\",{splits[1]}"
            lines += line

    with open(outname, "w", encoding="UTF-8") as file:
        file.writelines(lines)
    


if __name__ == "__main__":
    main("data/netflixdata")
