# Generated by Django 2.1.5 on 2021-04-26 15:56

import auctions.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0011_auto_20210426_1751'),
    ]

    operations = [
        migrations.AlterField(
            model_name='listing',
            name='imgfile',
            field=models.ImageField(default='default.png', upload_to=auctions.models.user_directory_path),
        ),
    ]
