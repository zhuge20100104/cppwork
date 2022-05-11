import os
import requests

headers = {'Authorization': 'Bearer 0fde144b7a220b7c76fe3077b01c1e231fe738fe'}
data = {
    "data": {
        "urls": [
            "https://api2.appannie.com/v2/bulk/data?name=metrics/app_store_ratings_product_level/all/all/daily/2019-05-01/data.10000001.20191031.3.csv.gz&signature=5974f32e1712c9880e74527745bae409",
            "https://api2.appannie.com/v2/bulk/data?name=dimensions/app_store_ratings_product_level/daily/2019-05-01/product_id.10000001.20191031.3.csv.gz&signature=c7614bd4ef82b9130004155d9de85e96",
        ]
    }
}

for url in data['data']['urls']:
    fname = url[url.find('name=')+5: url.rfind('.csv.gz')+7]
    path = f'/tmp/{fname}'
    print(f'Working on {path}')
    if not os.path.exists(os.path.dirname(path)):
        os.makedirs(os.path.dirname(path))
    resp = requests.get(url, headers=headers, allow_redirects=True, stream=True)
    import pdb; pdb.set_trace()
    if resp.status_code != 200:
        print('Skipped due to response error:')
        print(resp.content)
        continue
    print(resp.headers)
    with open(path, 'wb') as f:
        i, size = 1, 2*10
        for part in resp.iter_content(size):
            f.write(part)
            print('Saved {} bytes'.format(i*size))
            i += 1
        print(f'Saved file to: {path}')
print('[  OK  ]')