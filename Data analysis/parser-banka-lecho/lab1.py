import requests
from requests import get
from bs4 import BeautifulSoup
from warnings import warn
from time import sleep
from random import randint
import numpy as np, pandas as pd


def extract_pages(containers):
    for container in containers:
        if container.find('div', class_='ratings-metascore') is not None:
            title = container.h3.a.text
            titles.append(title)

            year = container.h3.find('span', class_='lister-item-year text-muted unbold')
            year_text = year.text if year is not None else None
            years.append(year_text)

            rating = container.p.find('span', class_='certificate')
            rating_text = rating.text if rating is not None else None
            ratings.append(rating_text)

            genre = container.p.find('span', class_='genre')
            genre_text = genre.text.replace("\n", "").rstrip().split(',') if genre is not None else None
            genres.append(genre_text)

            time = container.p.find('span', class_='runtime')
            time_text = int(time.text.replace(" min", "")) if time is not None else None
            runtimes.append(time_text)

            imdb = container.strong
            imdb_text = float(imdb.text) if imdb is not None else None
            imdb_ratings.append(imdb_text)

            m_score = container.find('span', class_='metascore')
            m_score_text = int(m_score.text) if m_score is not None else None
            metascores.append(m_score_text)

            nv = container.find_all('span', attrs={'name': 'nv'})

            vote_text = nv[0].text if len(nv) > 0 else None
            votes.append(vote_text)

            gross_text = nv[1].text if len(nv) > 1 else '-'
            grosses.append(gross_text)


def divide_film_containers():
    for page in pages:
        response = get("https://www.imdb.com/search/title?genres=sci-fi&"
                       + "start="
                       + str(page)
                       + "&explore=title_type,genres&ref_=adv_prv", headers=headers)

        sleep(randint(8, 15))
        if response.status_code != 200:
            warn('Request: {}; Status code: {}'.format(requests, response.status_code))

        html_page = BeautifulSoup(response.text, 'html.parser')
        film_containers = html_page.find_all('div', class_='lister-item mode-advanced')
        extract_pages(film_containers)


if __name__ == '__main__':
    pages = np.arange(1, 9950, 50)
    headers = {'Accept-Language': 'en-US,en;q=0.8'}

    titles = []
    years = []
    ratings = []
    genres = []
    metascores = []
    votes = []
    grosses = []
    runtimes = []
    imdb_ratings = []

    divide_film_containers()

    df = pd.DataFrame({'movie': titles,
                       'year': [year[-5:-1] for year in years],
                       'imdb_rate': imdb_ratings,
                       'metascore': metascores,
                       'votes': votes,
                       'rating': ratings,
                       'genre': genres,
                       'runtime_min': runtimes,
                       'grosess': grosses})

    final_df = df[df['year'] != 'ovie']
    final_df['year'] = pd.to_numeric(final_df['year'])
    csv_data = final_df.to_csv('imdbStat.csv', index=True)
